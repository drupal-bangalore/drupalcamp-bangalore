<?php

/**
 * @file
 * Campaign Monitor API call wrappers
 */

@require_once(drupal_get_path('module', 'emf_campaign_monitor') . '/CMBase.php');

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
function emf_campaign_monitor_api_subscribe($email, $fields, $lid) {
  // encode field keys
  $encoded = array();

  foreach ($fields as $key => $value) {
    $encoded['[' . $key . ']'] = $value;
  }

  $name = $encoded['[name]'];

  // do api call
  $result = _emf_campaign_monitor_api_call('subscriberAddWithCustomFields', array($email, $name, $encoded, $lid, TRUE));
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
function emf_campaign_monitor_api_unsubscribe($email, $lid) {
  // do api call
  $result = _emf_campaign_monitor_api_call('subscriberUnsubscribe', array($email, $lid, FALSE));

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
function emf_campaign_monitor_api_get_subscribers_subscribed($date = 0, $lid = NULL) {
  return _emf_campaign_monitor_api_get_subscribers_active($date, $lid);
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
function emf_campaign_monitor_api_get_subscribers_unsubscribed($date = 0, $lid = NULL) {
  return _emf_campaign_monitor_api_get_subscribers_active($date, $lid, 'Subscribers.GetUnsubscribed');
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
function _emf_campaign_monitor_api_get_subscribers_active($date = 0, $lid = NULL, $action = 'Subscribers.GetActive') {
  return _emf_campaign_monitor_api_get_scalar_array_call('subscribersGetActive', array($date, $lid, $action), 'Subscriber', 'EmailAddress');
}

/**
 * Fetch lists from API.
 *
 * @return
 *   Array; List of subscriber lists.
 */
function emf_campaign_monitor_api_get_lists() {
  $fields = array(
    'lid' => 'ListID',
    'name_api' => 'Name',
  );

  return _emf_campaign_monitor_api_get_array_call('clientGetLists', array(), 'List', $fields, 'lid');
}

/**
 * Fetch custom fields for some list from API.
 *
 * @param $lid
 *   String; List ID of the list.
 * @return
 *   Array; List of custom fields.
 */
function emf_campaign_monitor_api_get_custom_fields($lid) {
  $fields = array(
    'key' => 'Key',
    'name' => 'FieldName',
    'type' => 'DataType',
    'options' => 'FieldOptions',
  );

  // do call
  $result = _emf_campaign_monitor_api_get_array_call('listGetCustomFields', array($lid), 'ListCustomField', $fields, 'key');

  // field type mapping
  $field_type_mapping = array(
    'Text' => 'text',
    'Number' => 'text',
    'MultiSelectOne' => 'select_one',
    'MultiSelectMany' => 'select_many',
  );

  // cleaning up fields
  foreach ($result as $key => $value) {
    // converting type
    $result[$key]->type = $field_type_mapping[$result[$key]->type];

    // prettyfying options
    if (empty($result[$key]->options)) {
      unset($result[$key]->options);
    }
    else {
      $options = array();
      foreach ($result[$key]->options as $type => $type_options) {
        foreach ($type_options as $option) {
          $options[] = $option;
        }
      }
      $result[$key]->options = $options;
    }
  }

  // decoding field keys
  $decoded = array();
  foreach ($result as $field) {
    $key = drupal_substr($field->key, 1, drupal_strlen($field->key) - 2);
    $field->key = $key;
    $decoded[$key] = $field;
  }

  // adding name field since it's not passed by campaign monitor as a custom field
  $decoded['name'] = new stdClass();
  $decoded['name']->key = 'name';
  $decoded['name']->name = 'Name';
  $decoded['name']->type = 'text';

  return $decoded;
}

/**
 * Fetch sytem time.
 *
 * @return
 *   Integer; System time.
 */
function emf_campaign_monitor_api_get_system_time() {
  // do api call
  $result = _emf_campaign_monitor_api_call('userGetSystemDate');
  if ($result === FALSE) return FALSE;

  return $result['anyType'];
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
function _emf_campaign_monitor_api_call($method, $params = array()) {
   // fetching api key and client id
  $api_key = variable_get('emf_campaign_monitor_api_key', '');
  $client_id = variable_get('emf_campaign_monitor_client_id', '');

  // if no api key or client id is specified, return false
  if (empty($api_key) || empty($client_id)) return FALSE;

  // do api call
  $cm = new CampaignMonitor($api_key, $client_id);
  $result = call_user_func_array(array($cm, $method), $params);

  // if api result code is not 'ok', return false and write log
  if (is_array($result['anyType']) && array_key_exists('Code', $result['anyType']) && $result['anyType']['Code'] != 0) {
    watchdog('emf_campaign_monitor', 'Code - ' . $result['anyType']['Code'] . ', Message - ' . $result['anyType']['Message'], array(), WATCHDOG_ERROR);
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
function _emf_campaign_monitor_api_get_array_call($method, $params, $type, $fields, $key = NULL) {
  $items = array();

  // do api call
  $result = _emf_campaign_monitor_api_call($method, $params);

  if ($result === FALSE) return FALSE;

  // converting api result to array
  $api_fields = array_values($fields);
  if ($result['anyType'][$type][$api_fields[0]]) {
    // if we have only one list, convert it to an array
    $object = new stdClass();
    foreach ($fields as $local_field => $api_field)
    $object->{$local_field} = $result['anyType'][$type][$api_field];
    if ($key) {
      $items[$object->{$key}] = $object;
    }
    else {
      $items[] = $object;
    }
  }
  else {
    if (!empty($result['anyType'][$type])) {
      foreach ($result['anyType'][$type] as $item) {
        $object = new stdClass();
        foreach ($fields as $local_field => $api_field) {
          if (!empty($item[$api_field])) {
            $object->{$local_field} = $item[$api_field];
          }
          if ($key) {
            $items[$object->{$key}] = $object;
          }
          else {
            $items[] = $object;
          }
        }
      }
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
function _emf_campaign_monitor_api_get_scalar_array_call($method, $params, $type, $field) {
  $items = array();

  // do api call
  $result = _emf_campaign_monitor_api_call($method, $params);
  if ($result === FALSE) return FALSE;

  // converting api result to array
  if ($result['anyType'][$type][$field]) {
    // if we have only one subscriber, return it
    $items[] = $result['anyType'][$type][$field];
  }
  else {
    if (!empty($result['anyType'][$type])) {
      foreach ($result['anyType'][$type] as $item) {
        $items[] = $item[$field];
      }
    }
  }

  return $items;
}

/**
 * Convert a UNIX timestamp to a date Campaign Monitor wants to receive.
 *
 * @param $timestamp
 *   Integer; The UNIX timestamp to convert.
 * @retun
 *   String; The Date in Campaign Monitor format.
 */
function emf_campaign_monitor_api_unix_to_service_time($timestamp = 0) {
  if ($timestamp) {
    return date('Y-m-d H:i:s', $timestamp);
  }
  return 0;
}