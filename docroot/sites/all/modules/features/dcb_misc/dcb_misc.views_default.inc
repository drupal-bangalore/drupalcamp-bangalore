<?php
/**
 * @file
 * dcb_misc.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function dcb_misc_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'company_ticket_registrations';
  $view->description = 'List registrations by company';
  $view->tag = 'ticket';
  $view->base_table = 'ticket_registration';
  $view->human_name = 'Company Ticket Registrations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Companies';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view all ticket registrations';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'field_profile_first' => 'field_profile_first',
    'field_profile_last' => 'field_profile_last',
    'mail' => 'mail',
    'state' => 'state',
    'view_registration' => 'view_registration',
    'edit_registration' => 'edit_registration',
    'cancel_registration' => 'cancel_registration',
  );
  $handler->display->display_options['style_options']['default'] = 'field_profile_first';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_first' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_last' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
    'view_registration' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_registration' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'cancel_registration' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Ticket registration: Registrant */
  $handler->display->display_options['relationships']['author_uid']['id'] = 'author_uid';
  $handler->display->display_options['relationships']['author_uid']['table'] = 'ticket_registration';
  $handler->display->display_options['relationships']['author_uid']['field'] = 'author_uid';
  $handler->display->display_options['relationships']['author_uid']['required'] = TRUE;
  /* Field: Bulk operations: Ticket registration */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: User: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['relationship'] = 'author_uid';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['relationship'] = 'author_uid';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['relationship'] = 'author_uid';
  /* Field: User: Phone number */
  $handler->display->display_options['fields']['field_profile_phone']['id'] = 'field_profile_phone';
  $handler->display->display_options['fields']['field_profile_phone']['table'] = 'field_data_field_profile_phone';
  $handler->display->display_options['fields']['field_profile_phone']['field'] = 'field_profile_phone';
  $handler->display->display_options['fields']['field_profile_phone']['relationship'] = 'author_uid';
  /* Field: User: Location - Locality (i.e. City) */
  $handler->display->display_options['fields']['field_profile_location_locality']['id'] = 'field_profile_location_locality';
  $handler->display->display_options['fields']['field_profile_location_locality']['table'] = 'field_data_field_profile_location';
  $handler->display->display_options['fields']['field_profile_location_locality']['field'] = 'field_profile_location_locality';
  $handler->display->display_options['fields']['field_profile_location_locality']['relationship'] = 'author_uid';
  $handler->display->display_options['fields']['field_profile_location_locality']['label'] = 'City';
  /* Field: Ticket registration: Order state */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  /* Field: Ticket registration: Link */
  $handler->display->display_options['fields']['view_registration']['id'] = 'view_registration';
  $handler->display->display_options['fields']['view_registration']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['view_registration']['field'] = 'view_registration';
  $handler->display->display_options['fields']['view_registration']['label'] = '';
  $handler->display->display_options['fields']['view_registration']['element_label_colon'] = FALSE;
  /* Field: Ticket registration: Edit link */
  $handler->display->display_options['fields']['edit_registration']['id'] = 'edit_registration';
  $handler->display->display_options['fields']['edit_registration']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['edit_registration']['field'] = 'edit_registration';
  $handler->display->display_options['fields']['edit_registration']['label'] = '';
  $handler->display->display_options['fields']['edit_registration']['element_label_colon'] = FALSE;
  /* Field: Ticket registration: Cancel link */
  $handler->display->display_options['fields']['cancel_registration']['id'] = 'cancel_registration';
  $handler->display->display_options['fields']['cancel_registration']['table'] = 'ticket_registration';
  $handler->display->display_options['fields']['cancel_registration']['field'] = 'cancel_registration';
  $handler->display->display_options['fields']['cancel_registration']['label'] = '';
  $handler->display->display_options['fields']['cancel_registration']['element_label_colon'] = FALSE;
  /* Sort criterion: User: First name (field_profile_first) */
  $handler->display->display_options['sorts']['field_profile_first_value']['id'] = 'field_profile_first_value';
  $handler->display->display_options['sorts']['field_profile_first_value']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['sorts']['field_profile_first_value']['field'] = 'field_profile_first_value';
  $handler->display->display_options['sorts']['field_profile_first_value']['relationship'] = 'author_uid';
  /* Sort criterion: User: Last name (field_profile_last) */
  $handler->display->display_options['sorts']['field_profile_last_value']['id'] = 'field_profile_last_value';
  $handler->display->display_options['sorts']['field_profile_last_value']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['sorts']['field_profile_last_value']['field'] = 'field_profile_last_value';
  $handler->display->display_options['sorts']['field_profile_last_value']['relationship'] = 'author_uid';
  /* Contextual filter: Ticket registration: Ticket type ID (bundle) */
  $handler->display->display_options['arguments']['bundle']['id'] = 'bundle';
  $handler->display->display_options['arguments']['bundle']['table'] = 'ticket_registration';
  $handler->display->display_options['arguments']['bundle']['field'] = 'bundle';
  $handler->display->display_options['arguments']['bundle']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['bundle']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['bundle']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['bundle']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['bundle']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: User: Organization (field_profile_org) */
  $handler->display->display_options['arguments']['field_profile_org_value']['id'] = 'field_profile_org_value';
  $handler->display->display_options['arguments']['field_profile_org_value']['table'] = 'field_data_field_profile_org';
  $handler->display->display_options['arguments']['field_profile_org_value']['field'] = 'field_profile_org_value';
  $handler->display->display_options['arguments']['field_profile_org_value']['relationship'] = 'author_uid';
  $handler->display->display_options['arguments']['field_profile_org_value']['default_action'] = 'summary';
  $handler->display->display_options['arguments']['field_profile_org_value']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['field_profile_org_value']['title'] = 'Registrations for %2';
  $handler->display->display_options['arguments']['field_profile_org_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_profile_org_value']['summary']['sort_order'] = 'desc';
  $handler->display->display_options['arguments']['field_profile_org_value']['summary']['number_of_records'] = '1';
  $handler->display->display_options['arguments']['field_profile_org_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_profile_org_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_profile_org_value']['limit'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ticket_registration/manage/%/companies';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Company Ticket Registrations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-anonymous-user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['company_ticket_registrations'] = $view;

  $view = new view();
  $view->name = 'drupal_camp_sponsors';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Drupal Camp Sponsors';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '21600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Sponsor URL */
  $handler->display->display_options['fields']['field_sponsor_url']['id'] = 'field_sponsor_url';
  $handler->display->display_options['fields']['field_sponsor_url']['table'] = 'field_data_field_sponsor_url';
  $handler->display->display_options['fields']['field_sponsor_url']['field'] = 'field_sponsor_url';
  $handler->display->display_options['fields']['field_sponsor_url']['label'] = '';
  $handler->display->display_options['fields']['field_sponsor_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_sponsor_url']['alter']['text'] = '/node/[nid]';
  $handler->display->display_options['fields']['field_sponsor_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sponsor_url']['empty'] = '/sites/default/files/Brochure-DCB2015.pdf';
  $handler->display->display_options['fields']['field_sponsor_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_sponsor_url']['type'] = 'link_plain';
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_sponsor_logo']['id'] = 'field_sponsor_logo';
  $handler->display->display_options['fields']['field_sponsor_logo']['table'] = 'field_data_field_sponsor_logo';
  $handler->display->display_options['fields']['field_sponsor_logo']['field'] = 'field_sponsor_logo';
  $handler->display->display_options['fields']['field_sponsor_logo']['label'] = '';
  $handler->display->display_options['fields']['field_sponsor_logo']['alter']['text'] = '<a href="[field_sponsor_url]">[field_sponsor_logo]</a>';
  $handler->display->display_options['fields']['field_sponsor_logo']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_sponsor_logo']['alter']['path'] = '[field_sponsor_url]';
  $handler->display->display_options['fields']['field_sponsor_logo']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_sponsor_logo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sponsor_logo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sponsor_logo']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sponsor' => 'sponsor',
  );
  /* Filter criterion: Content: Sponsorship Level (field_sponsor_sponsorship_level) */
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['id'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['table'] = 'field_data_field_sponsor_sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['field'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['vocabulary'] = 'sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['hierarchy'] = 1;

  /* Display: Diamond Sponsors */
  $handler = $view->new_display('panel_pane', 'Diamond Sponsors', 'panel_pane_1');
  $handler->display->display_options['display_description'] = 'Diamond Sponsors';

  /* Display: Gold Sponsors */
  $handler = $view->new_display('panel_pane', 'Gold Sponsors', 'panel_pane_2');
  $handler->display->display_options['display_description'] = 'Gold Sponsors';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="silverspon-wrap gold-header"><h3>Gold Sponsors</h3></div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sponsor' => 'sponsor',
  );
  /* Filter criterion: Content: Sponsorship Level (field_sponsor_sponsorship_level) */
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['id'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['table'] = 'field_data_field_sponsor_sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['field'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['value'] = array(
    2 => '2',
  );
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['vocabulary'] = 'sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['hierarchy'] = 1;

  /* Display: Silver Sponsors */
  $handler = $view->new_display('panel_pane', 'Silver Sponsors', 'panel_pane_3');
  $handler->display->display_options['display_description'] = 'Silver Sponsors';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<div class="silverspon-wrap silver-header"><h3>Silver Sponsors</h3></div>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sponsor' => 'sponsor',
  );
  /* Filter criterion: Content: Sponsorship Level (field_sponsor_sponsorship_level) */
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['id'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['table'] = 'field_data_field_sponsor_sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['field'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['vocabulary'] = 'sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['hierarchy'] = 1;

  /* Display: Diamond Sponsors (Block) */
  $handler = $view->new_display('block', 'Diamond Sponsors (Block)', 'block_diamond');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '2';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['label'] = 'Block Title';
  $handler->display->display_options['footer']['area']['empty'] = TRUE;
  $handler->display->display_options['footer']['area']['content'] = 'Diamond Sponsors';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  $export['drupal_camp_sponsors'] = $view;

  $view = new view();
  $view->name = 'manage_people';
  $view->description = '';
  $view->tag = 'users';
  $view->base_table = 'users';
  $view->human_name = 'Manage People';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage People';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '200';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'uid' => 'uid',
    'name' => 'name',
    'mail' => 'mail',
    'field_profile_first' => 'field_profile_first',
    'field_profile_last' => 'field_profile_last',
    'field_profile_location_locality' => 'field_profile_location_locality',
    'created' => 'created',
    'view_user' => 'view_user',
    'edit_node' => 'edit_node',
    'cancel_node' => 'cancel_node',
  );
  $handler->display->display_options['style_options']['default'] = 'uid';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'sortable' => 1,
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
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_first' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_last' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_location_locality' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_user' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'cancel_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Bulk operations: User */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'users';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::user_block_user_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_user_cancel_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  /* Field: User: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  /* Field: User: Location - Locality (i.e. City) */
  $handler->display->display_options['fields']['field_profile_location_locality']['id'] = 'field_profile_location_locality';
  $handler->display->display_options['fields']['field_profile_location_locality']['table'] = 'field_data_field_profile_location';
  $handler->display->display_options['fields']['field_profile_location_locality']['field'] = 'field_profile_location_locality';
  $handler->display->display_options['fields']['field_profile_location_locality']['label'] = 'City';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'date_no_time';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'date_no_time';
  /* Field: User: Active */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: User: Link */
  $handler->display->display_options['fields']['view_user']['id'] = 'view_user';
  $handler->display->display_options['fields']['view_user']['table'] = 'users';
  $handler->display->display_options['fields']['view_user']['field'] = 'view_user';
  $handler->display->display_options['fields']['view_user']['label'] = '';
  $handler->display->display_options['fields']['view_user']['element_label_colon'] = FALSE;
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: User: Cancel link */
  $handler->display->display_options['fields']['cancel_node']['id'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['table'] = 'users';
  $handler->display->display_options['fields']['cancel_node']['field'] = 'cancel_node';
  $handler->display->display_options['fields']['cancel_node']['label'] = '';
  $handler->display->display_options['fields']['cancel_node']['element_label_colon'] = FALSE;
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/people/manage-people';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage People';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-anonymous-user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['manage_people'] = $view;

  return $export;
}
