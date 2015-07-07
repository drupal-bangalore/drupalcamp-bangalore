<?php
/**
 * @file
 * Default exported views.
 */

/**
 * Implements hook_views_default_views().
 */
function ticket_reservation_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ticket_reservation_orphaned_tickets';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ticket_registration';
  $view->human_name = 'Orphaned Tickets';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Orphaned Tickets';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit all ticket registrations';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'trid' => 'trid',
    'name' => 'name',
    'reservation_code' => 'reservation_code',
    'reservation_email' => 'reservation_email',
    'state' => 'state',
    'edit_registration' => 'edit_registration',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'trid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'reservation_code' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'reservation_email' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_registration' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  /* Relationship: Ticket registration: Author entity author_uid */
  $handler->display->display_options['relationships']['author']['id'] = 'author';
  $handler->display->display_options['relationships']['author']['table'] = 'ticket_registration';
  $handler->display->display_options['relationships']['author']['field'] = 'author';
  $handler->display->display_options['relationships']['author']['label'] = 'Author User';
  /* Field: Bulk operations: Ticket registration */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Modify Values',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'state' => 'state',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::panelizer_set_status_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Ticket registration: Ticket Registration ID */
  $handler->display->display_options['fields']['trid']['id'] = 'trid';
  $handler->display->display_options['fields']['trid']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['trid']['field'] = 'trid';
  $handler->display->display_options['fields']['trid']['label'] = 'ID';
  $handler->display->display_options['fields']['trid']['separator'] = '';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'author';
  $handler->display->display_options['fields']['name']['label'] = 'Registrar Username';
  /* Field: Ticket registration: Reservation Code */
  $handler->display->display_options['fields']['reservation_code']['id'] = 'reservation_code';
  $handler->display->display_options['fields']['reservation_code']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['reservation_code']['field'] = 'reservation_code';
  /* Field: Ticket registration: Reservation Email */
  $handler->display->display_options['fields']['reservation_email']['id'] = 'reservation_email';
  $handler->display->display_options['fields']['reservation_email']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['reservation_email']['field'] = 'reservation_email';
  /* Field: Ticket registration: Order state */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  /* Field: Ticket registration: Edit link */
  $handler->display->display_options['fields']['edit_registration']['id'] = 'edit_registration';
  $handler->display->display_options['fields']['edit_registration']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['edit_registration']['field'] = 'edit_registration';
  $handler->display->display_options['fields']['edit_registration']['label'] = '';
  $handler->display->display_options['fields']['edit_registration']['element_label_colon'] = FALSE;
  /* Contextual filter: Ticket registration: Ticket type ID (bundle) */
  $handler->display->display_options['arguments']['bundle']['id'] = 'bundle';
  $handler->display->display_options['arguments']['bundle']['table'] = 'ticket_registration';
  $handler->display->display_options['arguments']['bundle']['field'] = 'bundle';
  $handler->display->display_options['arguments']['bundle']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['bundle']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['bundle']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['bundle']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['bundle']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Ticket registration: User_uid */
  $handler->display->display_options['filters']['user_uid']['id'] = 'user_uid';
  $handler->display->display_options['filters']['user_uid']['table'] = 'ticket_registration';
  $handler->display->display_options['filters']['user_uid']['field'] = 'user_uid';
  $handler->display->display_options['filters']['user_uid']['value']['value'] = '0';
  $handler->display->display_options['filters']['user_uid']['group'] = 1;
  $handler->display->display_options['filters']['user_uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['user_uid']['expose']['operator_id'] = 'user_uid_op';
  $handler->display->display_options['filters']['user_uid']['expose']['label'] = 'User_uid';
  $handler->display->display_options['filters']['user_uid']['expose']['operator'] = 'user_uid_op';
  $handler->display->display_options['filters']['user_uid']['expose']['identifier'] = 'user_uid';
  $handler->display->display_options['filters']['user_uid']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['user_uid']['group_info']['label'] = 'Registrant UID';
  $handler->display->display_options['filters']['user_uid']['group_info']['identifier'] = 'user_uid';
  $handler->display->display_options['filters']['user_uid']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['user_uid']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['user_uid']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Unset',
      'operator' => '=',
      'value' => array(
        'value' => '0',
        'min' => '',
        'max' => '',
      ),
    ),
  );
  /* Filter criterion: Ticket registration: Author_uid */
  $handler->display->display_options['filters']['author_uid']['id'] = 'author_uid';
  $handler->display->display_options['filters']['author_uid']['table'] = 'ticket_registration';
  $handler->display->display_options['filters']['author_uid']['field'] = 'author_uid';
  $handler->display->display_options['filters']['author_uid']['group'] = 1;
  $handler->display->display_options['filters']['author_uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['author_uid']['expose']['operator_id'] = 'author_uid_op';
  $handler->display->display_options['filters']['author_uid']['expose']['label'] = 'Author_uid';
  $handler->display->display_options['filters']['author_uid']['expose']['operator'] = 'author_uid_op';
  $handler->display->display_options['filters']['author_uid']['expose']['identifier'] = 'author_uid';
  $handler->display->display_options['filters']['author_uid']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['author_uid']['group_info']['label'] = 'Author Uid';
  $handler->display->display_options['filters']['author_uid']['group_info']['identifier'] = 'author_uid';
  $handler->display->display_options['filters']['author_uid']['group_info']['widget'] = 'radios';
  $handler->display->display_options['filters']['author_uid']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Unset',
      'operator' => '=',
      'value' => array(
        'value' => '0',
        'min' => '',
        'max' => '',
      ),
    ),
  );
  /* Filter criterion: Ticket registration: Order state */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'ticket_registration';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['group'] = 1;
  $handler->display->display_options['filters']['state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['label'] = 'Order state';
  $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
  $handler->display->display_options['filters']['state']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    9 => 0,
    6 => 0,
    7 => 0,
    10 => 0,
    3 => 0,
    5 => 0,
    4 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ticket_registration/manage/%/orphans';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Orphaned Tickets';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $export['ticket_reservation_orphaned_tickets'] = $view;

  return $export;
}
