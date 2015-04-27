<?php
// $Id: emf_mailchimp.api.inc,v 1.3 2010/02/10 07:00:25 davyvandenbremt Exp $

/**
 * @file
 * MailChimp API call wrappers
 *
 * @author Davy Van Den Bremt
 */

@require_once(drupal_get_path('module', 'emf_mailchimp') . '/MCAPI.class.php');

/**
 * Subscribe a user to a list.
 *
 * @param $email
 *   String; E-mail address to subscribe
 * @param $fields
 *   Array; Array of custom field values. Key is field. Value is value for the field.
 * @param $lid
 *   String; List ID of the list to subscribe to.
 * @return
 *   Boolean; TRUE if user is subscribed. FALSE if not.
 */
function emf_mailchimp_api_subscribe($email, $fields, $lid) {
  // mailchimp subscribe can't handle blank merge_var arrays
  if (empty($fields)) {
    $fields = array('');
  }

  // do api call
  $result = _emf_mailchimp_api_call('listSubscribe', array($lid, $email, $fields, 'html', FALSE, TRUE));
  if (!$result) return FALSE;

  return TRUE;
}

/**
 * Unsubscribe a user from a list.
 *
 * @param $email
 *   String; E-mail address to subscribe
 * @param $lid
 *   String; List ID of the list to subscribe to.
 * @return
 *   Boolean; TRUE if user is subscribed. FALSE if not.
 */
function emf_mailchimp_api_unsubscribe($email, $lid) {
  // do api call
  $result = _emf_mailchimp_api_call('listUnsubscribe', array($lid, $email));

  if (!$result) return FALSE;

  return TRUE;
}

/**
 * Fetch subscribed subscribers from API.
 *
 * @param $date
 *   Mixed; If a string, should be in the date() format of 'Y-m-d H:i:s', otherwise, a Unix timestamp.
 * @param $lid
 *   String; List ID
 * @return
 *   Array; List of subscriber lists.
 */
function emf_mailchimp_api_get_subscribers_subscribed($date = 0, $lid = NULL) {
  return _emf_mailchimp_api_get_subscribers_active($date, $lid);
}

/**
 * Fetch unsubscribed subscribers from API.
 *
 * @param $date
 *   Mixed; If a string, should be in the date() format of 'Y-m-d H:i:s', otherwise, a Unix timestamp.
 * @param $lid
 *   String; List ID
 * @return
 *   Array; List of subscriber lists.
 */
function emf_mailchimp_api_get_subscribers_unsubscribed($date = 0, $lid = NULL) {
  return _emf_mailchimp_api_get_subscribers_active($date, $lid, 'unsubscribed');
}

/**
 * Fetch subscribers from API.
 *
 * @param $date
 *   Mixed; If a string, should be in the date() format of 'Y-m-d H:i:s', otherwise, a Unix timestamp.
 * @param $lid
 *   String; List ID
 * @param $action
 *   String; Set the actual API method to call. Defaults to Subscribers.GeActive if no other valid value is given.
 * @return
 *   Array; List of subscriber lists.
 */
function _emf_mailchimp_api_get_subscribers_active($date = 0, $lid = NULL, $action = 'subscribed') {
  return _emf_mailchimp_api_get_scalar_array_call('listMembers', array($lid, $action, $date, 0, 15000), 'email');
}

/**
 * Fetch lists from API.
 *
 * @return
 *   Array; List of subscriber lists.
 */
function emf_mailchimp_api_get_lists() {
  $fields = array(
    'lid' => 'id',
    'name_api' => 'name',
  );

  return _emf_mailchimp_api_get_array_call('lists', array(), $fields, 'lid');
}

/**
 * Fetch custom fields for some list from API.
 *
 * @param $lid
 *   String; List ID of the list.
 * @return
 *   Array; List of custom fields.
 */
function emf_mailchimp_api_get_custom_fields($lid) {
  $fields = array(
    'key' => 'tag',
    'name' => 'name',
    'type' => 'field_type',
    'options' => 'choices',
  );

  // do call
  $result = _emf_mailchimp_api_get_array_call('listMergeVars', array($lid), $fields, 'key');

  unset($result['EMAIL']);

  return $result;
}

/**
 * Do API call.
 *
 * @param $method
 *   String; The API method to call.
 * @param $params
 *   Array; Parameters for the API call.
 * @return
 *   Array; API result array.
 */
function _emf_mailchimp_api_call($method, $params = array()) {
   // fetching api key
  $api_key = variable_get('emf_mailchimp_api_key', '');

  // if no api key is specified, return false
  if (empty($api_key)) return FALSE;

  // do api call
  $mc = new MCAPI($api_key);
  $mc->setTimeout(15);
  $result = call_user_func_array(array($mc, $method), $params);

  // if api result code is not 'ok', return false and write log
  if ($mc->errorCode) {
    watchdog('emf_mailchimp', 'Code - ' . $mc->errorCode . ', Message - ' . $mc->errorMessage, array(), WATCHDOG_ERROR);
    return FALSE;
  }

  return $result;
}

/**
 * Do API call and parse the $results as an array.
 *
 * @param $method
 *   String; The API method to call.
 * @param $params
 *   Array; Parameters for the API call.
 * @param $type
 *   Array; API type used as index under $result['anyType'].
 * @param $fields
 *   Array; Indexed array for field mapping. Keys are local fields. Values are API fields.
 * @param $key
 *   String; Local field which value will be used to index the result array.
 * @return
 *   Array; Result array.
 */
function _emf_mailchimp_api_get_array_call($method, $params, $fields, $key = NULL) {
  $items = array();

  // do api call
  $results = _emf_mailchimp_api_call($method, $params);

  if (!$results) return FALSE;

  // converting api result to array
  foreach ($results as $result) {
    $object = new stdClass();
    foreach ($fields as $local_field => $api_field) {
      if (!empty($result[$api_field])) {
        $object->{$local_field} = $result[$api_field];
      }
    }
    if ($key) {
      $items[$object->{$key}] = $object;
    }
  }

  return $items;
}

/**
 * Do API call and parse the $results as an array.
 *
 * @param $method
 *   String; The API method to call.
 * @param $params
 *   Array; Parameters for the API call.
 * @param $type
 *   Array; API type used as index under $result['anyType'].
 * @param $field
 *   String; Field.
 * @return
 *   Array; Result array.
 */
function _emf_mailchimp_api_get_scalar_array_call($method, $params, $field) {
  $items = array();

  // do api call
  $results = _emf_mailchimp_api_call($method, $params);

  if (!$results) return FALSE;

  // converting api result to array
  foreach ($results as $result) {
    $items[] = $result[$field];
  }

  return $items;
}

/**
 * Convert a UNIX timestamp to a date MailChimp wants to receive.
 *
 * @param $timestamp
 *   Integer; The UNIX timestamp to convert.
 * @retun
 *   String; The Date in MailChimp format.
 */
function emf_mailchimp_api_unix_to_service_time($timestamp = 0) {
  if ($timestamp) {
    return date('Y-m-d H:i:s', $timestamp);
  }
  return 0;
}