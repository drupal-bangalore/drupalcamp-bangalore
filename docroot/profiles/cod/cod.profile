<?php

/*
 * Define commons minimum execution time required to operate.
 */
define('DRUPAL_MINIMUM_MAX_EXECUTION_TIME', 120);

/*
 * Define commons minimum opcode cache required to operate.
 */
define('COD_MINIMUM_OPCODE_CACHE', 96);

/**
 * Implements hook_form_alter().
 * Set COD as the default profile.
 * (copied from Atrium: We use system_form_form_id_alter, otherwise we cannot alter forms.)
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  foreach ($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'cod';
  }
}

function _cod_get_optional_modules() {
  $modules = system_rebuild_module_data();
  $cod_modules = array();
  foreach($modules AS $module_name => $module) {
    if(strpos($module_name, 'cod_') === 0 && isset($module->info['install_option']) && $module->info['install_option'] == 'cod') {
      $cod_modules[$module_name] = $module->info['description'] ? $module->info['description'] : $module_name;
    }
  }
  return $cod_modules;
}

/**
 * Return an array of permissions this module sets by default.
 */
function hook_cod_default_permissions() {
  return array('my_module' => array('user_permission', 'user_role'));
}


/** Default System Permissions
 * Features will eventually mess up someone's permissions for events, so they
 * need to be setup once during install and really never again.
 *
 * If a module needs to install new permissions, it should use this function
 * during install.
 * If a module needs to install a new role with permissions, it should use the
 * optional 'roles' parameter to avoid overwriting existing role<->permissions.
 *
 * @module the name of the module to grab permissions from.
 * @role (optional) install permissions only for a specific role.
 */
function cod_install_permissions($module, $roles = array()) {
  module_load_include('inc', $module, "$module.cod.user_permission");
  if (function_exists($module . '_user_initial_permissions') && $defaults = call_user_func($module . '_user_initial_permissions')) {
    // Make sure the list of available node types is up to date, especially when
    // installing multiple features at once, for example from an install profile
    // or via drush.
    node_types_rebuild();

    $modules = user_permission_get_modules();
    if (empty($roles)) {
      $roles = _user_features_get_roles();
    }
    $permissions_by_role = _user_features_get_permissions(FALSE);
    foreach ($defaults as $permission) {
      $perm = $permission['name'];
      _user_features_change_term_permission($perm, 'machine_name');
      if (empty($modules[$perm])) {
        $args = array('!name' => $perm, '!module' => $module,);
        $msg = t('Warning from !module: No module defines permission "!name".', $args);
        drupal_set_message($msg, 'warning');
        continue;
      }
      // Export vocabulary permissions using the machine name, instead of
      // vocabulary id.
      foreach ($roles as $role) {
        if (in_array($role, $permission['roles'])) {
          $permissions_by_role[$role][$perm] = TRUE;
        }
        else {
          $permissions_by_role[$role][$perm] = FALSE;
        }
      }
    }
    // Write the updated permissions.
    foreach ($roles as $rid => $role) {
      if (isset($permissions_by_role[$role])) {
        user_role_change_permissions($rid, $permissions_by_role[$role]);
      }
    }
  }
}

/*
 * Setup default roles.
 */
function cod_install_roles($module) {
  module_load_include('inc', $module, "$module.cod.user_role");
  if (function_exists($module . '_user_initial_roles') && $defaults = call_user_func($module . '_user_initial_roles')) {
    foreach ($defaults as $role) {
      $role = (object) $role;
      if ($existing = user_role_load_by_name($role->name)) {
        $role->rid = $existing->rid;
      }
      user_role_save($role);
    }
  }
}

/*
 * Setup default permissions og groups. Only creates permissions, doesn't revoke
 * unlike features, which does both.
 */
function cod_install_og_permissions($module, $roles = array()) {
  module_load_include('inc', $module, "$module.cod.og_permission");
  if (function_exists($module . '_og_initial_permissions') && $defaults = call_user_func($module . '_og_initial_permissions')) {
    $grant = array();
    $revoke = array();

    foreach ($defaults as $key => $details) {
      list($group_type, $bundle, $perm) = explode(':', $key);

      // Only add for roles existing in the group, don't revoke permissions
      if (empty($roles)) {
        $roles = og_roles($group_type, $bundle, 0);
      }
      foreach ($roles as $rid => $rolename) {
        if (in_array($rolename, $details['roles'])) {
          $grant[$rid][] = $perm;
        }
      }
    }

    if (!empty($grant)) {
      foreach ($grant as $rid => $permissions) {
        og_role_grant_permissions($rid, $permissions);
      }
    }
  }
}

/*
 * Create OG roles per group, basically events. (although could be others groups)
 */
function cod_install_og_roles($module) {
  $gids = &drupal_static(__FUNCTION__, FALSE);
  if (empty($gids)) {
    $gids = og_get_all_group('node');
  }
  module_load_include('inc', $module, "$module.cod.og_role");
  if (function_exists($module . '_og_initial_roles') && $defaults = call_user_func($module . '_og_initial_roles')) {
    foreach ($defaults as $key => $value) {
      list($group_type, $bundle, $name) = explode(':', $key);
      $role = (object) $value;
      if ($rid = _og_features_role_exists($name, $group_type, $bundle)) {
        $role->rid = $rid;
      }
      og_role_save($role);

      // Because all events default to overridden roles and permissions, we need to
      // Save the new role individually per conference.
      foreach ($gids AS $gid) {
        $role->gid = $gid;
        og_role_save($role);
      }
    }
  }
}