<?php

/**
 * @file
 * Defines an asymetric Mondrian inspired panels layout.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Header'),
  'icon' => 'preview.png',
  'category' => t('Drupalcamp content layouts'),
  'theme' => 'header',
  'regions' => array(
    'header_top' => t('Header Top'),
    'logo' => t('Logo'),
    'header_bottom' => t('Navigation'),
    
  ),
);
