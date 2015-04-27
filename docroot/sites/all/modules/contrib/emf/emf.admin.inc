<?php

/**
 * @file
 * Administration functions and callbacks.
 */

function emf_admin_lists() {
  drupal_add_css(drupal_get_path('module', 'emf') . '/emf-style.css');

  $header = array(t('Name'), t('List ID'), array('data' => t('Operations'), 'colspan' => 3));

  $lists = emf_db_get_lists();

  $rows = array();

  foreach ($lists as $list) {
    $rows[] = array(
      'data' => array(
        $list->name_api,
        $list->lid,
        l(t('Manage'), 'admin/structure/emf/' . $list->lid . '/manage'),
        l(t('View page'), 'emf/' . $list->lid),
        $list->status_api ? '' : l(t('Delete'), 'admin/structure/emf/' . $list->lid . '/delete'),
      ),
      'class' => $list->status_api ? array() : array('list-error'),
    );
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => t('No lists synchronised yet or no lists available in your account. Run cron to synchronise your lists.'), 'colspan' => '6', 'class' => array('message')));
  }
  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('emf-lists-table'))));
}

function emf_admin_list_info_form($form, &$form_values, $list = NULL) {
  $form = array();

  $status_api_description = t('This list was found in your e-mail marketing service. All is well.');

  if (!$list->status_api) {
    $status_api_description = t('This list could not be found (anymore) in your e-mail marketing service. Maybe you removed it? If so, you could decide to remove this list here to.');
    drupal_set_message($status_api_description, 'error');
  }

  $form['lid'] = array(
    '#type' => 'hidden',
    '#value' => $list->lid,
  );

  // api info
  $form['info_api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Info'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['info_api']['lid_display'] = array(
    '#type' => 'textfield',
    '#title' => t('List ID'),
    '#description' => t('The ID for this list as it is specified in your e-mail marketing service.'),
    '#disabled' => TRUE,
    '#default_value' => $list->lid,
  );
  $form['info_api']['name_api'] = array(
    '#type' => 'textfield',
    '#title' => t('API Name'),
    '#description' => t('The name for this list as it is specified in your e-mail marketing service.'),
    '#disabled' => TRUE,
    '#default_value' => $list->name_api,
  );
  $form['info_api']['status_api'] = array(
    '#type' => 'checkbox',
    '#title' => t('API Status'),
    '#description' => t($status_api_description),
    '#disabled' => TRUE,
    '#default_value' => $list->status_api,
  );
  $form['info_api']['value'] = array(
    '#type' => 'markup',
    '#value' => l(t('View subscription page'), 'emf/' . $list->lid),
  );

  // status
  $form['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status'),
    '#collapsible' => TRUE,
  );
  $form['status']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Activate on this site'),
    '#description' => t('If a list is not activated, it\'s fields and subscriptions will not be synced with your e-mail marketing service. Subscription will not be possible and no subscription block will be available for the list.'),
    '#default_value' => $list->status,
  );

  // language
  if ($languages = module_invoke('locale', 'language_list')) {
    $languages = array('' => t('Language neutral')) + $languages;

    $form['language'] = array(
      '#type' => 'fieldset',
      '#title' => t('Language'),
      '#collapsible' => TRUE,
    );
    $form['language']['language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#description' => t('Setting a list for a language means its block and its entry in the common subscription form will only appear on pages in that language.'),
      '#options' => $languages,
      '#default_value' => $list->language,
    );
  }

  // info
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Info'),
    '#collapsible' => TRUE,
  );
  $form['info']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t('The name of the list. This can differ from the name specified in your e-mail marketing service. An example of where the list name is used is in the subscription block title. You can use !name_api as a replacement variable.', array('!name_api' => '!name_api')),
    '#default_value' => $list->name,
    '#required' => TRUE,
  );
  $form['info']['name_action'] = array(
    '#type' => 'textfield',
    '#title' => t('Action name'),
    '#description' => t('The action name of the list. An example of where the list\'s action name is used is in the subscription form checkboxes. You can use !name and !name_api as replacement variables.', array('!name_api' => '!name_api', '!name' => '!name')),
    '#default_value' => $list->name_action,
    '#required' => TRUE,
  );
  $form['info']['name_action_long'] = array(
    '#type' => 'textfield',
    '#title' => t('Long action name'),
    '#description' => t('The long action name of the list. An example of where the list\'s long action name is used is in the subscription form intro text for anonymous users. You can use !name and !name_api as replacement variables.', array('!name_api' => '!name_api', '!name' => '!name')),
    '#default_value' => $list->name_action_long,
  );
  $form['info']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#description' => t('Description of this list. The value for this field will not be displayed but it can be used to document this list for future reference.'),
    '#default_value' => $list->description,
  );

  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function emf_admin_list_info_form_submit($form, &$form_state) {
  // fetching lid
  $lid = $form_state['values']['lid'];

  // fetching list from database
  $list = emf_db_get_list($lid);

  // setting all helper variables
  $name_api = $list->name_api;
  $status_api = $list->status_api;
  $name = $form_state['values']['name'];
  $status = $form_state['values']['status'];
  $name_action = $form_state['values']['name_action'];
  $name_action_long = $form_state['values']['name_action_long'];
  $description = $form_state['values']['description'];
  $language = isset($form_state['values']['language']) ? $form_state['values']['language'] : '';

  // saving to database
  emf_db_save_list($lid, $name_api, $status_api, $name, $status, $name_action, $name_action_long, $description, $language);

  // success message
  drupal_set_message(t('List modifications have been successfully saved.'));
}

function emf_admin_field_mapping_form($form, &$form_values, $list = NULL) {
  $form = array();

  // fetch profile fields
  $profile_fields  = array(-1 => t('Unmapped'));

  if (module_exists('profile')) {
    $result = db_query("SELECT title, name FROM {profile_field} ORDER BY title");
    while ($row = $result->fetchObject()) {
      $profile_fields[$row->name] = $row->title;
    }
  }

  if (count($profile_fields) == 1) {
    $profile_fields = array();
  }

  // fetching fields
  $list = emf_db_get_list($list->lid);
  $field_mapping = $list->field_mapping;

  // lid
  $form['lid'] = array(
    '#type' => 'hidden',
    '#value' => $list->lid,
  );

  // custom fields
  foreach ($field_mapping as $field) {
    $form[$field->key]['#tree'] = TRUE;
    $form[$field->key]['weight'] = array(
      '#type' => 'weight',
      '#default_value' => $field->weight,
    );
    $form[$field->key]['api_field'] = array(
      '#markup' => $field->name,
    );
    $form[$field->key]['account_field_type'] = array(
      '#type' => 'select',
      '#options' => array('php' => t('PHP code')),
      '#attributes' => array('class' => array('account_field_type')),
      '#default_value' => $field_mapping[$field->key]->mapping_type,
    );

    if (count($profile_fields) > 0) {
      $form[$field->key]['account_field_type']['#options']['profile'] = t('Profile');
    }

    if (module_exists('token')) {
      $form[$field->key]['account_field_type']['#options']['token'] = t('Token');
    }

    if (module_exists('token')) {
      $form[$field->key]['account_field_token'] = array(
        '#type' => 'textfield',
        '#size' => 30,
        '#attributes' => array('class' => array('account_field_token')),
        '#default_value' => $field_mapping[$field->key]->mapping_type == 'token' ? $field_mapping[$field->key]->mapping_value : '',
        '#states' => array(
        'visible' => array(
          '.account_field_type:input[name^=' . $field->key . ']' => array('value' => 'token')),
        )
      );
    }

    $form[$field->key]['account_field'] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#attributes' => array('class' => array('account_field')),
      '#default_value' => $field_mapping[$field->key]->mapping_type == 'php' ? $field_mapping[$field->key]->mapping_value : '',
      '#states' => array(
        'visible' => array(
          '.account_field_type:input[name^=' . $field->key . ']' => array('value' => 'php')
         ),
      )
    );

    if (count($profile_fields) > 0) {
      $form[$field->key]['account_field_profile'] = array(
        '#type' => 'select',
        '#options' => $profile_fields,
        '#attributes' => array('class' => array('account_field_profile')),
        '#default_value' => $field_mapping[$field->key]->mapping_type == 'profile' ? $field_mapping[$field->key]->mapping_value : '',
        '#states' => array(
          'visible' => array(
            '.account_field_type:input[name^=' . $field->key . ']' => array('value' => 'profile')
          ),
        )
      );
    }

    $form[$field->key]['anonymous_field'] = array(
      '#type' => 'checkbox',
      '#default_value' => $field_mapping[$field->key]->show_anonymous,
    );

    if (in_array($field->key, array('mail'))) {
      $form[$field->key]['anonymous_field']['#disabled'] = TRUE;
    }

    $form[$field->key]['common_form_show'] = array(
      '#type' => 'checkbox',
      '#default_value' => $field_mapping[$field->key]->common_form_show,
    );

    if (in_array($field->key, array('mail'))) {
      $form[$field->key]['common_form_show']['#disabled'] = TRUE;
    }
  }

  // submit
  if (!empty($field_mapping)) {
    if (module_exists('token')) {
      $form['token_help'] = array(
        '#title' => t('Token replacement patterns'),
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#description' => t('Prefer raw-text replacements for text to avoid problems with HTML entities!'),
      );

      $form['token_help']['help'] = array(
        '#theme' => 'token_tree',
        '#token_types' => array('user'),
        '#global_types' => FALSE,
      );
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
  }

  return $form;
}

function theme_emf_admin_field_mapping_form($variables) {

  $form = $variables['form'];

  $output = '';
  $header = array(t('List field'), t('Mapping source'), t('Source value'), t('Ask anonymous'), t('Show in common form'), t('Weight'));

  $rows = array();
  foreach ($form as $name => $element) {
    if (is_array($element) && isset($element['api_field']) && is_array($element['api_field'])) {
      $element['weight']['#attributes']['class'] = array('emf-admin-fields-weight');
      $rows[] = array(
        'data' => array(
          drupal_render($element['api_field']),
          drupal_render($element['account_field_type']),
          drupal_render($element['account_field_profile']) . drupal_render($element['account_field']) . drupal_render($element['account_field_token']),
          drupal_render($element['anonymous_field']),
          drupal_render($element['common_form_show']),
          drupal_render($element['weight']),
        ),
        'class' => array('draggable'),
      );
      unset($form[$name]);
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No fields synchronised yet or no fields available for this list. Run cron to synchronise your e-mail marketing service account.'), 'colspan' => '5', 'class' => array('message')));
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'emf-admin-field-mapping')));
  $output .= drupal_render_children($form);

  drupal_add_tabledrag('emf-admin-field-mapping', 'order', 'sibling', 'emf-admin-fields-weight', NULL, NULL, TRUE);

  return $output;
}

function emf_admin_field_mapping_form_submit($form, &$form_state) {
  // get lid
  $lid = $form_state['values']['lid'];

  // get current fields
  $list = emf_db_get_list($lid);
  $mapping = $list->field_mapping;

  // constructing mappign in db format
  foreach ($form as $key => $element) {
    if (isset($element['api_field']) && is_array($element['api_field'])) {
      $field = $form_state['values'][$key];
      unset($mapping[$key]->mapping_type);
      unset($mapping[$key]->mapping_value);
      unset($mapping[$key]->show_anonymous);
      unset($mapping[$key]->common_form_show);
      if ($field['account_field_type'] == 'profile' && $field['account_field_profile'] != -1) {
        $mapping[$key]->mapping_value = $field['account_field_profile'];
      }
      if ($field['account_field_type'] == 'php' && !empty($field['account_field'])) {
        $mapping[$key]->mapping_value = $field['account_field'];
      }
      if ($field['account_field_type'] == 'token' && !empty($field['account_field_token'])) {
        $mapping[$key]->mapping_value = $field['account_field_token'];
      }

      if (!empty($mapping[$key]->mapping_value)) {
        $mapping[$key]->mapping_type = $field['account_field_type'];
      }

      $mapping[$key]->show_anonymous = $field['anonymous_field'];
      $mapping[$key]->common_form_show = $field['common_form_show'];

      $mapping[$key]->weight = $field['weight'];
    }
  }

  // saving the mapping
  emf_db_save_field_mapping($lid, $mapping);

  // success message
  drupal_set_message(t('Mapping modifications have been successfully saved.'));
}

function emf_admin_roles_form($form, &$form_state, $list) {
  $form = array();

  $form['lid'] = array(
    '#type' => 'hidden',
    '#value' => $list->lid,
  );

  // list roles as options array
  $default_role_options = array();
  $result = db_query("SELECT rid FROM {emf_list_roles} WHERE lid = :lid", array(':lid' => $list->lid));
  while ($role = $result->fetchObject()) {
    $default_role_options[$role->rid] = $role->rid;
  }

  // all roles as options array
  $roles = user_roles();
  $role_options = array();
  foreach ($roles as $rid => $name) {
    $role_options[$rid] = $name;
  }

  $form['roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allow subscription for specific roles'),
    '#default_value' => $default_role_options,
    '#options' => $role_options,
    '#description' => t('If a user has any of the roles checked, he will be able to subscribe to this list and see its block, page etc.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

function emf_admin_roles_form_submit($form, &$form_state) {
  db_query("DELETE FROM {emf_list_roles} WHERE lid = :lid", array(':lid' => $form_state['values']['lid']));

  $roles = array_filter($form_state['values']['roles']);
  foreach ($roles as $rid) {
    db_query("INSERT INTO {emf_list_roles} (lid, rid) VALUES (:lid, :rid)", array(':lid' => $form_state['values']['lid'], ':rid' => $rid));
  }

  // success message
  drupal_set_message(t('Role modifications have been successfully saved.'));
}

function emf_admin_delete_confirm_form($form, &$form_state, $list) {
  $form['lid'] = array(
    '#type' => 'value',
    '#value' => $list->lid,
  );

  return confirm_form($form,
    t('Are you sure you want to delete %name?', array('%name' => $list->name_api)),
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/structure/emf',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

function emf_admin_delete_confirm_form_submit($form, &$form_state) {
  emf_db_delete_list($form_state['values']['lid']);

  // success message
  drupal_set_message(t('List has been successfully deleted. All requests will be deleted. Subscriptions that were already pushed will still exists on your e-mail marketing service account.'));

  $form_state['redirect'] = 'admin/structure/emf';
}