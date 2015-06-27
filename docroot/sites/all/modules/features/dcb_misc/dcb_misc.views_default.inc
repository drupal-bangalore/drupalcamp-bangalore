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
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
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
  $handler->display->display_options['fields']['field_sponsor_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sponsor_url']['alter']['text'] = '/node/[nid]';
  $handler->display->display_options['fields']['field_sponsor_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sponsor_url']['empty'] = '/sites/default/files/Brochure-DCB2015.pdf';
  $handler->display->display_options['fields']['field_sponsor_url']['click_sort_column'] = 'url';
  /* Field: Content: Logo */
  $handler->display->display_options['fields']['field_sponsor_logo']['id'] = 'field_sponsor_logo';
  $handler->display->display_options['fields']['field_sponsor_logo']['table'] = 'field_data_field_sponsor_logo';
  $handler->display->display_options['fields']['field_sponsor_logo']['field'] = 'field_sponsor_logo';
  $handler->display->display_options['fields']['field_sponsor_logo']['label'] = '';
  $handler->display->display_options['fields']['field_sponsor_logo']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_sponsor_logo']['alter']['text'] = '<a href="[field_sponsor_url]">[field_sponsor_logo]</a>';
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
  /* Filter criterion: Field: Sponsorship Level (field_sponsor_sponsorship_level) */
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
  /* Filter criterion: Field: Sponsorship Level (field_sponsor_sponsorship_level) */
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
  /* Filter criterion: Field: Sponsorship Level (field_sponsor_sponsorship_level) */
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['id'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['table'] = 'field_data_field_sponsor_sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['field'] = 'field_sponsor_sponsorship_level_tid';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['vocabulary'] = 'sponsorship_level';
  $handler->display->display_options['filters']['field_sponsor_sponsorship_level_tid']['hierarchy'] = 1;
  $export['drupal_camp_sponsors'] = $view;

  return $export;
}
