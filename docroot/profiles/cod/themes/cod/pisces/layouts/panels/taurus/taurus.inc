<?php
// Plugin definition
$plugin = array(
  'title' => t('Taurus'),
  'icon' => 'taurus.png',
  'category' => t('COD'),
  'theme' => 'taurus',
  'css' => '../../../css/panels/taurus/taurus.css',
  'regions' => array(
    'left_header' => t('Left Header'),
    'right_header' => t('Right Header'),
    'left_triptych' => t('Left Triptych'),
    'middle_triptych' => t('Middle Triptych'),
    'right_triptych' => t('Right Triptych'),
    'left_content' => t('Left Content'),
    'right_content' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
