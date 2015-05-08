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
   * its display can be customised in the view mode. Video does not have a field
   * and the only way to render the atom's main content is by rendering it using
   * its player.
   *
   * @Issue("Extend support to other video providers apart from YouTube")
   * @Issue("Implement similar approach for other atom types as needed")
   */
  function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    if ($entity->type !== 'video') {
      return $build;
    }

    $build['atom'] = array(
      '#type' => 'markup',
      '#markup' => theme(
        'scald_youtube_player',
        array('vars' =>
          array(
            'video_id'      => $entity->base_id,
            'video_width'   => ($entity->data['video_width'] ? $entity->data['video_width'] : 480),
            'video_height'  => ($entity->data['video_height'] ? $entity->data['video_height'] : 365),
          ),
        )
      ),
    );

    return $build;
  }
}
