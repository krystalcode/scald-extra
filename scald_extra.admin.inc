<?php
/**
 * @file
 * Administration pages for the scald_extra module.
 */

/**
 * Returns the configuration form.
 */
function scald_extra_admin_settings($form, &$form_state) {
  $form['scald_extra_generate_contexts'] = array(
    '#type' => 'select',
    '#title' => t('The image styles to generate contexts for'),
    '#options' => array(
      'all' => t('All'),
      'numeric' => t('Numeric'),
      'none' => t('None'),
    ),
    '#default_value' => variable_get('scald_extra_generate_contexts', 'all'),
    '#description' => t('When the "All" option is selected, Scald Extra will automatically generate a scald context for all image styles available. The automatically generated contexts will render the atom simply as the image without any of its metadata, using the corresponding image style. This way images added to content items can be easily rendered using any image style desired.<br />When the "Numeric" option is selected, contexts will be generated only for image styles that follow the naming convention "width"x"height" e.g. 100x100 or simply 100 as its machine_name.<br /><br /><strong>Remember to clear all caches</strong> when changing this setting, otherwise the changes will not have any effect.'),
  );

  $form['scald_extra_generate_thumbnails'] = array(
    '#type' => 'select',
    '#title' => t('The image styles to pre-generate thumbnails for'),
    '#options' => array(
      'all' => t('All'),
      'numeric' => t('Numeric'),
      'none' => t('None'),
    ),
    '#default_value' => variable_get('scald_extra_generate_thumbnails', TRUE),
    '#description' => t('Generate thumbnails for all image styles when uploading an image (thumbnail) for an atom. This can help to avoid performance issues in the case that many images are uploaded or updated, or to avoid problems that happen sometimes with the thumbnails not being generated until the next time the cache is cleared. The meaning of the Numeric option is the same as with the generating contexts.<br /><br />Note that thumbnails will be generated <strong>only when an atom image is uploaded through the UI</strong> on the website and not programatically due to lack of an appropriate hook in the scald core module.'),
  );

  // Icons.
  // @Issue("Add check whether the icon module is enabled")
  $icon_defaults = _scald_extra_icon_defaults();

  if (module_exists('scald_audio')) {
    $defaults = variable_get('scald_extra_audio_icon');
    $form['scald_extra_audio_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the audio scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['audio'],
    );
  }

  if (module_exists('scald_file')) {
    $defaults = variable_get('scald_extra_file_icon');
    $form['scald_extra_file_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the file scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['file'],
    );
  }

  if (module_exists('scald_image')) {
    $defaults = variable_get('scald_extra_image_icon');
    $form['scald_extra_image_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the image scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['image'],
    );
  }

  if (
    module_exists('scald_dailymotion') ||
    module_exists('scald_vimeo') ||
    module_exists('scald_youtube')
  ) {
    $defaults = variable_get('scald_extra_video_icon');
    $form['scald_extra_video_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the video scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['video'],
    );
  }

  if (module_exists('scald_url')) {
    $defaults = variable_get('scald_extra_url_icon');
    $form['scald_extra_url_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the url scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['url'],
    );
  }

  if (module_exists('scald_iframe')) {
    $defaults = variable_get('scald_extra_iframe_icon');
    $form['scald_extra_iframe_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the iframe scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['iframe'],
    );
  }

  if (module_exists('scald_embed')) {
    $defaults = variable_get('scald_extra_embed_icon');
    $form['scald_extra_embed_icon'] = array(
      '#type' => 'icon_selector',
      '#title' => t('The icon to use for the embed scald atom type'),
      '#default_bundle' => !empty($defaults['bundle']) ? $defaults['bundle'] : $icon_defaults['bundle'],
      '#default_icon' => !empty($defaults['icon']) ? $defaults['icon'] : $icon_defaults['icons']['embed'],
    );
  }

  return system_settings_form($form);
}
