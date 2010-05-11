<?php
class apachesolr_views_node_user_type extends apachesolr_views_handler_filter_type {
  public function get_value_options() {
    parent::get_value_options();
    $this->value_options['user'] = t('User');
  }
}