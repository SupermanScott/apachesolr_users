<?php
/**
 * @file:
 * provides apachesolr_views intergration with users data
 */

/**
 * Implemetnation of hook_views_handlers().
 */
function apachesolr_users_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'apachesolr_users') . '/views',
    ),
    'handlers' => array(
      'apachesolr_views_node_user_type' => array(
        'parent' => 'apachesolr_views_handler_filter_type',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data_alter().
 */
function apachesolr_users_views_data_alter(&$data) {
  $data['apachesolr']['type']['filter']['handler'] = 'apachesolr_views_node_user_type';
  
  // roles
  $role_key = apachesolr_index_key(array('index_type' => 'integer', 'multiple' => TRUE, 'name' => 'rid'));
  $data['apachesolr'][$role_key] = array(
    'title' => t('Users Role'),
    'help' => t('A users role'),
    'filter' => array(
      'handler' => 'apachesolr_views_handler_filter_single',
    ),
  );
}