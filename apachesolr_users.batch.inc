<?php
// $Id: $

/**
 * @file:
 * Contains the batch api functions for rebuild the solr index for users.
 */

/**
 * Batch index users in chunks.
 */
function apachesolr_users_batch_index(&$context) {
  require_once './' . drupal_get_path('module', 'apachesolr') . '/SolrPhpClient/Apache/Solr/Document.php';

  if (empty($context['sandbox'])) {
    try {
      // Get the $solr object
      $solr = apachesolr_get_solr();
      // If there is no server available, don't continue.
      if (!$solr->ping()) {
        throw new Exception(t('No Solr instance available during indexing.'));
      }
    }
    catch (Exception $e) {
      watchdog('Apache Solr', $e->getMessage(), NULL, WATCHDOG_ERROR);
      return FALSE;
    }
    $indexing_variables = variable_get('apachesolr_users_last_index', array('last_modify' => 0, 'last_uid' => 0));
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = db_result(db_query("SELECT COUNT(uid) FROM {apachesolr_users_queue} WHERE status > 0 AND (modified > %d OR modified = %d AND uid > %d)", $indexing_variables['last_modify'], $indexing_variables['last_modify'], $indexing_variables['last_uid']));

    if (empty($context['sandbox']['max'])) {
      return $context['finished'] = TRUE;
    }
  }

  $context['sandbox']['progress'] += apachesolr_users_cron();

  $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
}