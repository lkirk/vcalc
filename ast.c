#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

vc_ast_node_t *new_vc_op_node(enum vc_op op, vc_ast_node_t *left,
                              vc_ast_node_t *right) {
  vc_op_node_t *op_node = malloc(sizeof(vc_op_node_t));
  vc_ast_node_t *node = malloc(sizeof(vc_ast_node_t));

  op_node->op = op;
  op_node->left = left;
  op_node->right = right;

  node->node.n = op_node;
  node->type = VC_OP_NODE;

  return node;
}

vc_ast_node_t *new_vc_value_node(enum vc_value value_type, vc_value_t value) {
  vc_value_node_t *value_node = malloc(sizeof(vc_value_node_t));
  vc_ast_node_t *node = malloc(sizeof(vc_ast_node_t));

  value_node->value_type = value_type;
  value_node->value = value;
  node->node.v = value_node;
  node->type = VC_VALUE_NODE;

  return node;
}

vc_ast_node_t *new_vc_variable_node(const char *name, vc_value_node_t *value) {
  vc_var_node_t *var_node = malloc(sizeof(vc_var_node_t));
  vc_ast_node_t *node = malloc(sizeof(vc_ast_node_t));

  var_node->name = name;
  var_node->value = value;

  node->node.var = var_node;
  node->type = VC_VAR_NODE;
  return node;
}

vc_scope_t *vc_scope_init() { return kh_init(str_to_vc_value); }

void vc_scope_put(vc_scope_t *scope, const char *key, vc_value_node_t *val) {
  int ret;
  khint_t k = kh_put_str_to_vc_value(scope, key, &ret);
  kh_val(scope, k) = *val;
}

vc_value_node_t *vc_scope_get(vc_scope_t *scope, const char *key) {
  khint_t k = kh_get_str_to_vc_value(scope, key);
  if (k == kh_end(scope)) { // value is missing
    return NULL;
  }
  return &(kh_val(scope, k));
}

void vc_node_print(vc_ast_node_t *ast) {
  if (ast->type == VC_VALUE_NODE) {
    printf("value:\n");
  } else if (ast->type == VC_VAR_NODE) {
    printf("variable:\n");
  }
}
