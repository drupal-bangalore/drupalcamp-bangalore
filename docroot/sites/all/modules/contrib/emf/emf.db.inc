<?php

/**
 * @file
 * Database wrapper functions.
 */

/**
 * Fetch requests from database;
 *
 * @return
 *   Array; List of requests.
 */
function emf_db_get_requests() {
  $requests = array();
  $result = db_query("SELECT * FROM {emf_request} ORDER BY timestamp ASC");
  while ($request = $result->fetchObject()) {
    $request->fields = empty($request->fields) ? array() : unserialize($request->fields);
    $requests[$request->mail] = $request;
  }
  return $requests;
}

/**
 * Save a request to database.
 *
 * @param $type
 *   String; Type of request; 'subscribe' or 'unsubscribe'.
 * @param $mail
 *   String; The mail address the request is for.
 * @param $lid
 *   String; The list id the request is for.
 * @param $fields
 *   Array; Values for fields to subscribe.
 */
function emf_db_save_request($type, $mail, $lid, $fields = array(), $fails = 0) {
  $exists = db_query("SELECT mail FROM {emf_request} WHERE mail = :mail AND lid = :lid", array(':mail' => $mail, ':lid' => $lid))->fetchField();
  if ($exists) {
    db_query("UPDATE {emf_request} SET type = :type, fields = :fields, timestamp = :now, fails = :fails WHERE mail = :mail AND lid = :lid", array(
      ':now' => REQUEST_TIME,
      ':type' => $type,
      ':fields' =>  serialize($fields),
      ':mail' => $mail,
      ':lid' => $lid,
      ':fails' => $fails,
    ));
  }
  else {
    db_query("INSERT INTO {emf_request} (type, mail, lid, fields, timestamp, fails) VALUES (:type, :mail, :lid, :fields, :now, :fails)", array(
      ':now' => REQUEST_TIME,
      ':type' => $type,
      ':mail' => $mail,
      ':lid' => $lid,
      ':fields' => serialize($fields),
      ':fails' => $fails
    ));
  }
}

/**
 * Delete a request from database.
 *
 * @param $mail
 *   String; The mail address the request is for.
 * @param $lid
 *   String; The list id the request is for.
 */
function emf_db_delete_request($mail, $lid) {
  db_query("DELETE FROM {emf_request} WHERE mail = :mail AND lid = :lid", array(':mail' => $mail, ':lid' => $lid));
}

/**
 * Fetch subscriptions for a given address.
 *
 * @param $mail
 *   String; The mail address to fetch subscriptions for.
 * @result
 *   Array; Array of list id's of the lists the address is subscribed to.
 */
function emf_db_get_subscriptions($mail) {
  $lists = array();
  $result = db_query("SELECT lid FROM {emf_subscription} WHERE mail = :mail", array(':mail' => $mail));
  while ($lid = $result->fetchField()) {
    $lists[] = $lid;
  }
  return $lists;
}

/**
 * Save a subscriptions for a given address to a given list.
 *
 * @param $mail
 *   String; The mail address to save the subscription for.
 * @param $lid
 *   String; The list id save the subscription for.
 */
function emf_db_save_subscription($mail, $lid) {
  $exists = db_query("SELECT mail FROM {emf_subscription} WHERE mail = :mail AND lid = :lid",  array(':mail' => $mail, ':lid' => $lid))->fetchField();
  if (!$exists) {
    db_query("INSERT INTO {emf_subscription} (mail, lid) VALUES (:mail, :lid)", array(':mail' => $mail, ':lid' => $lid));
  }
}

/**
 * Delete a subscription for a given address to a given list.
 *
 * @param $mail
 *   String; The mail address to delete the subscription for.
 * @param $lid
 *   String; The list id delete the subscription for.
 */
function emf_db_delete_subscription($mail, $lid) {
  db_query("DELETE FROM {emf_subscription} WHERE mail = :mail AND lid = :lid", array(':mail' => $mail, ':lid' => $lid));
}

/**
 * Fetch a list.
 *
 * @param $lid
 *   String; The list id of the list to fetch.
 * @result
 *   Object; The list object.
 */
function emf_db_get_list($lid = 0) {
  if (!$lid) {
    return FALSE;
  }
  $list = db_query("SELECT * FROM {emf_list} WHERE lid = :lid", array(':lid' => $lid))->fetchObject();
  if (empty($list)) {
    return FALSE;
  }
  $list->field_mapping = empty($list->field_mapping) ? array() : unserialize($list->field_mapping);
  _emf_db_sort_field_mapping($list->field_mapping);
  array_walk($list->field_mapping, '_emf_db_clean_field_mapping');
  $list->name_clean = strtr($list->name, array('!name_api' => $list->name_api));
  $list->name_action_clean = strtr($list->name_action, array('!name_api' => $list->name_api, '!name' => $list->name_clean));
  $list->name_action_long_clean = strtr($list->name_action_long, array('!name_api' => $list->name_api, '!name' => $list->name_clean));

  return $list;
}

function _emf_db_sort_field_mapping(&$mapping) {
  uasort($mapping, '_emf_db_field_mapping_sort');
}

function _emf_db_field_mapping_sort($a, $b) {
  if ($a->weight == $b->weight) return 0;
  return ($a->weight < $b->weight) ? -1 : 1;
}

function _emf_db_clean_field_mapping(&$mapping) {
  static $properties = array(
    'weight' => 0,
    'mapping_type' => 'php',
    'mapping_value' => FALSE,
    'show_anonymous' => FALSE,
    'common_form_show' => FALSE
  );
  foreach ($properties as $property => $default_value) {
    if (!isset($mapping->$property)) {
      $mapping->$property = $default_value;
    }
  }
}

/**
 * Fetch all lists.
 *
 * @param $active_only
 *   Boolean; TRUE to only fetch active lists. FALSE if all.
 * @result
 *   Array; Array of list objects.
 */
function emf_db_get_lists($active_only = FALSE) {
  $lists = array();

  // only fetch active lists
  $filter = '';
  if ($active_only) {
    $filter = ' WHERE status = 1';
  }

  $result = db_query("SELECT * FROM {emf_list}$filter");
  while ($row = $result->fetchObject()) {
    $row->field_mapping = empty($row->field_mapping) ? array() : unserialize($row->field_mapping);
    _emf_db_sort_field_mapping($row->field_mapping);
    $lists[$row->lid] = $row;
    $lists[$row->lid]->name_clean = strtr($lists[$row->lid]->name, array('!name_api' => $lists[$row->lid]->name_api));
    $lists[$row->lid]->name_action_clean = strtr($lists[$row->lid]->name_action, array('!name_api' => $lists[$row->lid]->name_api, '!name' => $lists[$row->lid]->name_clean));
    $lists[$row->lid]->name_action_long_clean = strtr($lists[$row->lid]->name_action_long, array('!name_api' => $lists[$row->lid]->name_api, '!name' => $lists[$row->lid]->name_clean));
  }

  return $lists;
}

/**
 * Save a list.
 *
 * @param $lid
 *   String; List id of the list.
 * @param $name_api
 *   String; Name of the list on the API.
 * @param $status_api
 *   Integer; Status on the api of the list.
 * @param $name
 *   String; Site name for the list.
 * @param $status
 *   Integer; Status of the list.
 * @param $name_action
 *   String; Action name for the list.
 * @param $name_action_long
 *   String; Long action name for the list.
 * @param $description
 *   String; Description for the list.
 */
function emf_db_save_list($lid, $name_api, $status_api, $name, $status, $name_action, $name_action_long, $description, $language) {
  $exists = db_query("SELECT lid FROM {emf_list} WHERE lid = :lid", array(':lid' => $lid))->fetchField();
  if ($exists) {
    db_query("UPDATE {emf_list} SET name_api = :name_api, status_api = :status_api, name = :name, status = :status, name_action = :name_action, name_action_long = :name_action_long, description = :description, language = :language WHERE lid = :lid", array(':name_api' => $name_api, ':status_api' => $status_api, ':name' => $name, ':status' => $status, ':name_action' => $name_action, ':name_action_long' => $name_action_long, ':description' => $description, ':language' => $language, ':lid' => $lid));
  }
  else {

    db_query("INSERT INTO {emf_list} (lid, name_api, status_api, name, status, name_action, name_action_long, description, language, field_mapping) VALUES (:lid, :name_api, :status_api, :name, :status, :name_action, :name_action_long, :description, :language, '')", array(':lid' => $lid, ':name_api' => $name_api, ':status_api' => $status_api, ':name' => $name, ':status' => $status, ':name_action' => $name_action, ':name_action_long' => $name_action_long, ':description' => $description, ':language' => $language));
  }
}

/**
 * Delete a list and all its request and subscriptions.
 *
 * @param $lid
 *   String; List id of the list to delete.
 */
function emf_db_delete_list($lid) {
  db_query("DELETE FROM {emf_list} WHERE lid = :lid", array(':lid' => $lid));
  db_query("DELETE FROM {emf_request} WHERE lid = :lid", array(':lid' => $lid));
  db_query("DELETE FROM {emf_subscription} WHERE lid = :lid", array(':lid' => $lid));
  db_query("DELETE FROM {emf_list_roles} WHERE lid = :lid", array(':lid' => $lid));
}

/**
 * Save a field mapping for a given list.
 *
 * @param $lid
 *   String; List id of the list to save the mapping for.
 * @param $field_mapping
 *   Array; Field mapping to save.
 */
function emf_db_save_field_mapping($lid, $field_mapping = array()) {
  db_query("UPDATE {emf_list} SET field_mapping = :field_mapping WHERE lid = :lid", array(':field_mapping' => serialize($field_mapping), ':lid' => $lid));
}