<?php
/**
 * Create and return a table.
 */
function login_watch_create_counter_table() {
  $perpage = 10;
  $rows = array();
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
  $result = login_watch_create_counter_query($header, $perpage);
  $rows = login_watch_fill_counter_table($result);
  $table_counter = theme('table', array('header' => $header, 'rows' => $rows));
  $table_counter .= theme('pager');
  return $table_counter;
}
/**
 * Create a query from DB to fill the table.
 */
function login_watch_create_counter_query($header, $perpage) {
  $query = db_select('login_tracker', 'l')
    ->extend('TableSort')
    ->extend('PagerDefault')
    ->fields('u', array('name'))
    ->orderByHeader($header)
    ->limit($perpage);
  $query->innerJoin('users', 'u', 'u.uid = l.uid');
  $query->addExpression('COUNT(*)', 'counter');
  $query->GroupBy('l.uid');
  $result = $query->execute();
  return $result;
}
/**
 * Fill the table.
 */
function login_watch_fill_counter_table($result) {
  $rows = array();
  while ($value = $result->fetchAssoc()) {
    $rows[] = array(
      $value['name'],
      $value['counter'],
    );
  }
  return $rows;
}
