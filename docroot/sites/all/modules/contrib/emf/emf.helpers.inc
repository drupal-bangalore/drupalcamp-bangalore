<?php

/**
 * @file
 * Helper functions used by all files.
 */

function emf_helpers_parse_field_values($lid, $account = NULL) {
  global $user;

  if (!$account) {
    $account = $user;
  }

  $values = array();

  $list = emf_db_get_list($lid);

  foreach ($list->field_mapping as $field) {
    // php mapping
    if ($field->mapping_type == 'php') {

      $result = '';
      ob_start();
      $code = $field->mapping_value;
      $result = eval($code);
      ob_end_clean();

      $values[$field->key] = $result;
    }

    // profile mapping
    elseif ($field->mapping_type == 'profile' && module_exists('profile')) {
      // TODO: Is this needed, if $account is a properly loaded user object, profile fields are already loaded.
      profile_user_load(array($account->uid => &$account));
      if (!empty($account->{$field->mapping_value})) {
        $values[$field->key] = $account->{$field->mapping_value};
      }
    }

    // token mapping
    elseif ($field->mapping_type == 'token' && module_exists('token')) {
      if (module_exists('profile')) {
        // TODO: Is this needed, if $account is a properly loaded user object, profile fields are already loaded.
        profile_user_load(array($account->uid => &$account));
      }

      $token_pattern = $field->mapping_value;
      $context['user'] =& $account;
      $values[$field->key] = token_replace($token_pattern, $context);
    }
  }

  return $values;
}

/**
 * Subscribe a user to a list.
 *
 * @param $mail
 *   String; E-mail address to subscribe
 * @param $lid
 *   String; List ID of the list to subscribe to.
 * @param $fields
 *   Array; Array of custom field values. Key is field. Value is value for the field.
 */
function emf_helpers_subscribe($mail, $lid, $fields) {
  emf_db_save_request('subscribe', $mail, $lid, $fields);
  emf_db_save_subscription($mail, $lid);
}

/**
 * Unsubscribe a user from a list.
 *
 * @param $mail
 *   String; E-mail address to unsubscribe
 * @param $lid
 *   String; List ID of the list to unsubscribe from.
 */
function emf_helpers_unsubscribe($mail, $lid) {
  emf_db_save_request('unsubscribe', $mail, $lid);
  emf_db_delete_subscription($mail, $lid);
}

/**
 * Check if a certain sync action is allowed to happen.
 *
 * @param $type
 *   String; Type of sync, used in the variable name.
 * @return
 *   Boolean; TRUE if sync can happen; FALSE if not.
 */
function _emf_allow_sync($type) {
  $frequency = variable_get('emf_sync_' . $type . '_interval', 0);
  $last_sync = variable_get('emf_last_sync_' . $type, 0);

  if ($frequency > -1 && ($_SERVER['REQUEST_TIME'] - $last_sync > $frequency)) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Check if a certain user has permission to subscribe to a list.
 *
 * @param $lid
 *   String; The list id to permission has to be checked for.
 * @return
 *   Boolean; TRUE if user has permission; FALSE if not.
 */
function emf_user_access($lid) {
  global $user;

  // superuser has access to all lists
  if ($user->uid == 1) return TRUE;

  // check roles
  $result = db_query("SELECT rid FROM {emf_list_roles} WHERE lid = :lid", array(':lid' => $lid));
  while ($role= $result->fetchObject()) {
    if (in_array($role->rid, array_keys($user->roles))) {
      return TRUE;
    }
  }
  return FALSE;
}

function emf_list_visibile($lid) {
  $list = emf_db_get_list($lid);

  if (variable_get('language_count', 1) > 1 && !empty($list->language) && $list->language != $GLOBALS['language']->language) {
    return FALSE;
  }

  if ($list->status && emf_user_access($list->lid)) {
    return TRUE;
  }

  return FALSE;
}