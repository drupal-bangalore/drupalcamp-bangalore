<?php

/**
 * @file
 * Hooks provided by the Inline Conditions module.
 */

/**
 * Defines inline conditions.
 *
 * Inline Conditions are configured and added through a field attached
 * to the parent entity (discount, shipping rate, etc) based on which the
 * rule is built. When the rule is being built, the module providing the
 * parent entity type calls inline_conditions_build_rule,
 * which in turn calls the build callback of each configured inline condition.
 * Based on the user provided configuration, the build callback adds an
 * actual rules condition to the passed rule.
 *
 * Supported keys:
 * - label: The human readable label, shown in the UI (field widget).
 * - entity type: The type of the entity available to the rule, on which the
 *   condition can operate. This is the main criteria on which conditions are
 *   selected for showing in the field widget.
 * - rule condition name: (Optional) Rule condition machine name. This rule
 *   condition will be use instead of the inline condition name. If this
 *   key is set, the build callback is optional.
 * - parent entity type: (Optional) The type of the parent entity type (that
 *   contains the Inline Conditions field), used to further limit the
 *   availability of the condition (so a condition could choose to be shown
 *   only for Order Discounts, but not Shipping Services, even though both
 *   operate on the same entity type -> commerce_order).
 * - callbacks: An array of callbacks:
 *   - configure: (Optional) Returns a configuration form embedded into the
 *     field widget, and used to configure the inline condition.
 *   - build: [Do not use if rule condition name is set] Gets the rule and any
 *     settings added by the configure callback, then builds and adds an actual
 *     rules condition to the rule. Also, if the rule condition name key is set,
 *     this parameter is no longer available.
 */
function hook_inline_conditions_info() {
  $conditions = array();
  $conditions['inline_conditions_order_total'] = array(
    'label' => t('Orders over'),
    'entity type' => 'commerce_order',
    //'rule condition name' => 'data_is'
    'callbacks' => array(
      'configure' => 'inline_conditions_order_total_configure',
      'build' => 'inline_conditions_order_total_build',
    ),
  );

  return $conditions;
}

/**
 * Alter the condition info.
 *
 * @param array $conditions
 *   An array of inline conditions.
 *
 * @see hook_inline_conditions_info().
 */
function hook_inline_conditions_info_alter(&$conditions) {
  $conditions['inline_conditions_order_total']['label'] = t('Order total over');
}

/**
 * Alter fields values before building the rule.
 *
 * @param array $value
 *   Current value found in an inline conditions field type.
 *
 * @see inline_conditions_build().
 */
function hook_inline_conditions_build_alter(&$value) {
  if ($value['condition_name'] == 'commerce_order_has_owner') {
    // Do your stuff here.
  }
}
