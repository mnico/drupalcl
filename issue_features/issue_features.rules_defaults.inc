<?php
/**
 * @file
 * issue_features.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function issue_features_default_rules_configuration() {
  $items = array();
  $items['rules_enviar_correo_issues'] = entity_import('rules_config', '{ "rules_enviar_correo_issues" : {
      "LABEL" : "Nuevo Comentario Issue",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Issue" ],
      "REQUIRES" : [ "flag", "rules", "comment" ],
      "ON" : { "comment_insert--comment_node_issue" : { "bundle" : "comment_node_issue" } },
      "DO" : [
        { "flag_fetch_users_node" : {
            "USING" : { "flag" : "subscripcion_issue", "node" : [ "comment:node" ] },
            "PROVIDE" : { "users" : { "users" : "Users who flagged" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "mail" : {
                  "to" : [ "list-item:mail" ],
                  "subject" : "Nuevo comentario al issue [comment:node]",
                  "message" : "[comment:body]\\r\\n\\r\\nGG",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
