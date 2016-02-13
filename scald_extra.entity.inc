<?php

/**
 * Controller used for rendering an atom using the view modes.
 */
class ScaldAtomEntityAPIController extends EntityAPIController {
  /**
   * Implements EntityAPIControllerInterface.
   *
   * The entity_build_content function used by the parent function cannot build
   * the content because the entity passed to it is the default atom that
   * implements the ScaldAtomController class but does not implement the
   * EntityAPIControllerInterface interface that provides the buildContent
   * function.
   *
   * We override the parent view function only to manually call the correct
   * buildContent function defined in this controller.
   */
  public function view($entities, $view_mode = 'full', $langcode = NULL, $page = NULL) {
    // For Field API and entity_prepare_view, the entities have to be keyed by
    // (numeric) id.
    $entities = entity_key_array_by_property($entities, $this->idKey);
    if (!empty($this->entityInfo['fieldable'])) {
      field_attach_prepare_view($this->entityType, $entities, $view_mode);
    }
    entity_prepare_view($this->entityType, $entities);
    $langcode = isset($langcode) ? $langcode : $GLOBALS['language_content']->language;

    $view = array();
    foreach ($entities as $entity) {
      // Do not use entity_build_content for the reasons explained in the
      // function comments.
      $build = $this->buildContent($entity, $view_mode, $langcode);
      $build += array(
        // If the entity type provides an implementation, use this instead the
        // generic one.
        // @see template_preprocess_entity()
        '#theme' => 'entity',
        '#entity_type' => $this->entityType,
        '#entity' => $entity,
        '#view_mode' => $view_mode,
        '#language' => $langcode,
        '#page' => $page,
      );
      // Allow modules to modify the structured entity.
      drupal_alter(array($this->entityType . '_view', 'entity_view'), $build, $this->entityType);
      $key = isset($entity->{$this->idKey}) ? $entity->{$this->idKey} : NULL;
      $view[$this->entityType][$key] = $build;
    }
    return $view;
  }

  /**
   * Implements EntityAPIControllerInterface.
   *
   * Image and file atom types have a field file as the atom's main content and
   * its display can be customised in the view mode. URL and Video does not have
   * a field and the only way to render the atom's main content is by rendering
   * it using its player. Audio atom type does have a field, however we want to
   * render the audio player as well.
   */
  function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    if (!in_array($entity->type, array('audio', 'url', 'video'))) {
      return $build;
    }

    $function = 'build' . ucfirst($entity->type) . 'Content';
    $build = $this->$function($build, $entity, $view_mode, $langcode, $content);

    return $build;
  }

  /**
   * @see $this->buildContent().
   */
  function buildAudioContent($build, $entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build['atom'] = array(
      '#type' => 'markup',
      '#markup' => theme(
        'scald_audio_player',
        array('vars' =>
          array(
            'atom'      => $entity,
            'audio_uri' => $entity->file_source,
            'thumbnail' => $entity->thumbnail_source,
          ),
        )
      ),
    );

    return $build;
  }

  /**
   * @see $this->buildContent().
   */
  function buildUrlContent($build, $entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build['atom'] = array(
      '#type' => 'markup',
      '#markup' => theme(
        'scald_url_iframe_player',
        array('vars' =>
          array(
            'iframe_url'    => $entity->{SCALD_URL_URL_FIELD}[$entity->language][0]['url'],
            'iframe_width'  => (!empty($entity->data['width']) ? $entity->data['width'] : '100%'),
            'iframe_height' => (!empty($entity->data['height']) ? $entity->data['height'] : '500px'),
          ),
        )
      ),
    );

    return $build;
  }

  /**
   * @see $this->buildContent().
   *
   * @Issue(
   *   "Extend support to other video providers apart from YouTube",
   *   type="improvement",
   *   priority="normal"
   * )
   */
  function buildVideoContent($build, $entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $video_width = isset($entity->data['video_width']) ? $entity->data['video_width'] : 480;
    $video_height = isset($entity->data['video_height']) ? $entity->data['video_height'] : 365;
    $list = isset($entity->data['list']) ? '?list=' . $entity->data['list'] : '';

    $query = array();
    if (!empty($entity->data['list'])) {
      $query['list'] = $entity->data['list'];
    }
    if (isset($entity->data['show_related']) && empty($entity->data['show_related'])) {
      $query['rel'] = '0';
    }
    $video_url = url(SCALD_YOUTUBE_EMBED . $entity->base_id, array(
      'query' => $query,
    ));

    $build['atom'] = array(
      '#type' => 'markup',
      '#markup' => theme(
        'scald_youtube_player',
        array(
          'vars' => array(
            'video_id'     => $entity->base_id,
            'video_width'  => $video_width,
            'video_height' => $video_height,
            'video_url'    => $video_url,
            /**
             * @Issue(
             *   "Pass the rendered thumbnail as well"
             *   type="task"
             *   priority="low"
             * )
             */
            // 'thumbnail'    => $entity->rendered->thumbnail_source_url,
            'title'        => check_plain($entity->title),
          ),
        )
      ),
    );

    return $build;
  }
}
