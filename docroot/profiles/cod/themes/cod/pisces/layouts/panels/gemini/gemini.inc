<?php
// Plugin definition
$plugin = array(
  'title' => t('Gemini'),
  'icon' => 'gemini.png',
  'category' => t('COD'),
  'theme' => 'gemini',
  'css' => '../../../css/panels/gemini/gemini.css',
  'regions' => array(
    'preface' => t('Preface'),
    'left_header' => t('Left Header'),
    'right_header' => t('Right Header'),
    'middle' => t('Middle'),
    'left_content' => t('Left Content'),
    'right_content' => t('Right Content'),
    'footer' => t('Footer'),
  ),
);
