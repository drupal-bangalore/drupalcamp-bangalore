<?php

/**
 * @file
 * Report functions and callbacks.
 */

function emf_reports_subscriptions() {
  $header = array(t('List'), t('Subscribers'));

  $query = db_select('emf_subscription', 'cs');
  $query->join('emf_list', 'cl', 'cl.lid = cs.lid');
  $query->fields('cl', array('lid', 'name_api'));
  $query->addExpression('count(cs.mail)', 'subscribers');
  $query->groupBy('cl.lid');
  $result = $query->execute();

  $rows = array();

  while ($list = $result->fetchObject()) {
    $rows[] = array(
      l($list->name_api, 'admin/structure/emf/' . $list->lid . '/manage'),
      $list->subscribers,
    );
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No lists synchronised yet or no lists available in your account. Run cron to synchronise your lists.'), 'colspan' => '4', 'class' => array('message')));
  }

  return array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
}

function emf_reports_requests() {
  $header = array(t('Mail'), t('List'), t('Type'), t('Date'));

  $query = db_select('emf_request', 'r')->extend('PagerDefault');
  $query->join('emf_list', 'l', 'r.lid = l.lid');
  $query->fields('r')->fields('l')->orderBy('timestamp', 'DESC')->limit(10);

  $result = $query->execute();

  $rows = array();
  foreach ($result as $request) {
    $rows[] = array(
      $request->mail,
      l($request->name_api, 'admin/structure/emff/' . $request->lid . '/manage'),
      $request->type,
      t('!time ago', array('!time' => format_interval(REQUEST_TIME - $request->timestamp))),
    );
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No requests pending.'), 'colspan' => '4', 'class' => array('message')));
  }

  return array(
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
    'pager' => array(
      '#theme' => 'pager',
      '#quantity' => 50
    ),
  );
}