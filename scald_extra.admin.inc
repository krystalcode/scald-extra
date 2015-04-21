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
    '#description' => t('When the "All" option is selected, Scald Extra will automatically generate a scald context for all image styles available. The automatically generated contexts will render the atom simply as the image without any of its metadata, using the corresponding image style. This way images added to content items can be easily rendered using any image style desired. When the "Numeric" option is selected, contexts will be generated only for image styles that follow the naming convention "width"x"height" e.g. 100x100 or simply 100 as its machine_name. Remember to clear all caches when changing this setting, otherwise the changes will not have any effect.'),
  );

  $form['scald_extra_generate_thumbnails'] = array(
    '#type' => 'select',
    '#title' => t('The image styles to pre-generate thumbnails'),
    '#options' => array(
      'all' => t('All'),
      'numeric' => t('Numeric'),
      'none' => t('None'),
    ),
    '#default_value' => variable_get('scald_extra_generate_thumbnails', TRUE),
    '#description' => t('Generate thumbnails for all image styles when uploading an image (thumbnail) for an atom. This can help to avoid performance issues in the case that many images are uploaded or updated, or to avoid problems that happen sometimes with the thumbnails not being generated until the next time the cache is cleared. The meaning of the Numeric option is the same as with the generating contexts.'),
  );

  return system_settings_form($form);
}
