<?php
/**
 * Create a query from DB to fill the table.
 */
function login_watch_create_counter_query() {
  $query = db_select('login_tracker', 'l')
    ->extend('TableSort')
    ->extend('PagerDefault')
    ->fields('u', array('name'))
    ->limit(20)
    ->orderBy('counter', 'DESC');
  $query->innerJoin('users', 'u', 'u.uid = l.uid');
  $query->addExpression('COUNT(*)', 'counter');
  $query->GroupBy('l.uid');
  $result = $query->execute();
  return theme_counter(array('query' => $result));
}
/**
 * Theming function.
 */
function theme_counter($variables) {
  $rows = array();
  $header = array(
    array('data' => t('username')),
    array('data' => t('counter')) ,
  );
  while ($value = $variables['query']->fetchAssoc()) {
    $rows[] = array(
      $value['name'],
      $value['counter'],
  );
  $output = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No login history available.'),
  );
  return $output;
  }
}
