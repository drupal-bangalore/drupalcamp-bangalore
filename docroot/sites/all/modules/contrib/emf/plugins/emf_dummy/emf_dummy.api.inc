<?php

/**
 * @file
 * Dummy API call wrappers
 *
 */

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
function emf_dummy_api_subscribe($email, $fields, $lid) {
  $variable_name = 'emf_dummy_subscriptions_' . $lid;
  $subscriptions = variable_get($variable_name, array());
  $subscriptions[$email] = $fields;
  variable_set($variable_name, $subscriptions);
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
function emf_dummy_api_unsubscribe($email, $lid) {
  $variable_name = 'emf_dummy_subscriptions_' . $lid;
  $subscriptions = variable_get($variable_name, array());
  unset($subscriptions[$email]);
  variable_set($variable_name, $subscriptions);
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
function emf_dummy_api_get_subscribers_subscribed($date = 0, $lid = NULL) {
  $variable_name = 'emf_dummy_subscribed_' . $lid;
  return variable_get($variable_name, array());
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
function emf_dummy_api_get_subscribers_unsubscribed($date = 0, $lid = NULL) {
  $variable_name = 'emf_dummy_unsubscribed_' . $lid;
  return variable_get($variable_name, array());
}


/**
 * Fetch lists from API.
 *
 * @return
 *   Array; List of subscriber lists.
 */
function emf_dummy_api_get_lists() {
  $variable_name = 'emf_dummy_lists';
  return variable_get($variable_name, array());
}

/**
 * Fetch custom fields for some list from API.
 *
 * @param $lid
 *   String; List ID of the list.
 * @return
 *   Array; List of custom fields.
 */
function emf_dummy_api_get_custom_fields($lid) {
  $variable_name = 'emf_dummy_custom_fields';
  return array_merge(variable_get($variable_name, array()), variable_get($variable_name . '_' . $lid, array()));
}

/**
 * Convert a UNIX timestamp to a UNIX timestamp.
 *
 * @param $timestamp
 *   Integer; The UNIX timestamp to convert.
 * @retun
 *   String; The Date in Campaign Monitor format.
 */
function emf_dummy_api_unix_to_service_time($timestamp = 0) {
  return $timestamp;
}