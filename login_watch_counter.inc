<?php
/**
 * Implement login counter function.
 */
function login_watch_counter() {
  //Create the table.
  $rows = array();
  $header = array(
    array(
      'data' => t('username'),
      'field' => 'name' ,
      'sort' => 'desc'
    ),
    array(
      'data' => t('counter'),
      'field' => 'counter',
    ),
  );
  // Count every user login value.
//   $count = db_query("SELECT name, count(*) AS counter FROM {login_tracker} INNER JOIN users USING(uid) GROUP BY uid");
  $query = db_select('login_tracker', 'l')->extend('TableSort')->extend('PagerDefault');
  $query->innerJoin('users', 'u', 'u.uid = l.uid');
  $query->fields('u', array('users'));
  $query->addExpression('COUNT(*) AS counter');
  $query->GroupBy('l.uid')
$count = $query->execute()->fetchField();
  // Fill the table.
  while ($value = $count->fetchAssoc()) {
    $rows[] = array(
      $value['name'],
      $value['counter'],
    );
  }
  // Render the table.
  $table_counter = theme('table', array('header' => $header, 'rows' => $rows));
  return $table_counter;
}
