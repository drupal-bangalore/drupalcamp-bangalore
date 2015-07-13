<?php
/**
 * @file
 * dcb_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function dcb_rules_default_rules_configuration() {
  $items = array();
  $items['rules_registration_for_event_while_signup'] = entity_import('rules_config', '{ "rules_registration_for_event_while_signup" : {
      "LABEL" : "Registration for Event while signup",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "registration", "slack" ],
      "REQUIRES" : [ "rules", "slack", "ticket" ],
      "ON" : { "ticket_registration_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "ticket-registration:bundle" ], "value" : "2" } }
      ],
      "DO" : [
        { "slack_send_message" : { "message" : "Registration received by [ticket-registration:author:field-profile-first] [ticket-registration:author:field-profile-last] ([ticket-registration:author:mail]) for [ticket-registration:user:mail]" } }
      ]
    }
  }');
  $items['rules_send_slack_notification_on_session_submission'] = entity_import('rules_config', '{ "rules_send_slack_notification_on_session_submission" : {
      "LABEL" : "Send Slack Notification on Session submission",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "session", "slack" ],
      "REQUIRES" : [ "rules", "slack" ],
      "ON" : {
        "node_insert--session" : { "bundle" : "session" },
        "node_update--session" : { "bundle" : "session" }
      },
      "DO" : [
        { "slack_send_message" : { "message" : "[node:author:field-profile-first] [node:author:field-profile-last] ([node:author:mail]) has just submitted a session on *[node:title]* under *[node:og-vocabulary]* track." } }
      ]
    }
  }');
  return $items;
}
