<?php
/**
 * Simple login counter function.
 */
function login_watch_counter() {
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
  // Count every user login value.
  $query = db_select('login_tracker', 'l')->extend('TableSort')->extend('PagerDefault');
  $query->innerJoin('users', 'u', 'u.uid = l.uid');
  $query->fields('u', array('name'))->orderByHeader($header)->limit($perpage);
  $query->addExpression('COUNT(*)', 'counter');
  $query->GroupBy('l.uid');
  $count = $query->execute();
  // Fill the table.
  while ($value = $count->fetchAssoc()) {
    $rows[] = array(
      $value['name'],
      $value['counter'],
    );
  }
  // Render the table.
  $table_counter = theme('table', array('header' => $header, 'rows' => $rows));
  $table_counter .= theme('pager');
  return $table_counter;
}
