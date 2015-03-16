<?php
/**
 * Create and render a table.
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
  $count = counter_query($header, $perpage);
  $rows = fill_counter_table($count);
  $table_counter = theme('table', array('header' => $header, 'rows' => $rows));
  $table_counter .= theme('pager');
  return $table_counter;
}
/**
 * Create a query from DB to fill the table.
 */
function counter_query($header, $perpage) {
  $query = db_select('login_tracker', 'l')->extend('TableSort')->extend('PagerDefault');
  $query->innerJoin('users', 'u', 'u.uid = l.uid');
  $query->fields('u', array('name'))->orderByHeader($header)->limit($perpage);
  $query->addExpression('COUNT(*)', 'counter');
  $query->GroupBy('l.uid');
  $count = $query->execute();
  return $count;
}
/**
 * Fill the table.
 */
function fill_counter_table($count) {
  $rows = array();
  while ($value = $count->fetchAssoc()) {
    $rows[] = array(
      $value['name'],
      $value['counter'],
    );
  }
  return $rows;
}
