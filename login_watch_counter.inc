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
  $count = db_query("SELECT name, count(*) as counter FROM {login_tracker} INNER JOIN users using(uid) group by uid");
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
