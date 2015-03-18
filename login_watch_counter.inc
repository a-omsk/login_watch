<?php
/**
 * Create a query from DB to fill the table.
 */
function login_watch_create_counter_query() {
  $query = db_select('login_tracker', 'l')
    ->extend('TableSort')
    ->extend('PagerDefault')
    ->fields('u', array('name'))
    ->orderByHeader($header)
    ->limit(10);
  $query->innerJoin('users', 'u', 'u.uid = l.uid');
  $query->addExpression('COUNT(*)', 'counter');
  $query->GroupBy('l.uid');
  $result = $query->execute()->fetchAllAssoc();
  return $result;
}
/**
 * Implements theme_table.
 */
 function login_watch_counter_table() {
  $perpage = 10;
  $result = login_watch_create_counter_query();
  $header = array(
    array(
      'data' => t('username'),
      'field' => 'name' ,
      'sort' => 'asc'
    ),
    array(
      'data' => t('counter'),
      'field' => 'counter',
    ),
  );
  $rows = array();
   while ($value = $result) {
    $rows[] = array(
      $value['name'],
      $value['counter'],
    );
  }
  $output = theme('table', array('header' => $header, 'rows' => $rows));
  $output .= theme('pager');
  return $output;
}
