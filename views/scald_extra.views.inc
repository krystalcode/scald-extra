<?php
/**
 * @file
 * Views plugins implementation.
 */

/**
 * Implements hook_views_plugins().
 */
function scald_extra_views_plugins() {
  return array(
    'display' => array(
      'scald_extra_dnd_library' => array(
        'title' => t('Scald Extra Library'),
        'help' => t('Format atoms for use as a DnD Library'),
        'handler' => 'scald_extra_plugin_display_library',
        'parent' => 'page',
        'path' => drupal_get_path('module', 'scald_extra') . '/views',
        'theme' => 'views_view',
        'use ajax' => FALSE,
        'use pager' => TRUE,
        'admin' => t('Library'),
        'help topic' => 'scald-library',
        'uses hook menu' => TRUE,
        'provides dnd library' => TRUE,
      ),
    ),
  );
}
