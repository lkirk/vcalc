#include <stdio.h>
#include <stdlib.h>

#include "ast.h"

// int SYMBOL_TABLE[256] = {};

// TODO: union type for ast nodes
// does this work?????
// typedef union {
//   struct vc_ast_node *node;
//   struct vc_value_node *value;
// } * vc_ast_node_t;

// typedef struct vc_ast_node {
//   union {
//     struct vc_ast_node *node;
//     struct vc_value_node *value;
//   } * left;
//   union {
//     struct vc_ast_node *node;
//     struct vc_value_node *value;
//   } * right;
//   enum vc_node_type node_type;
//   enum vc_op op_type;
// } vc_ast_node_t;

// typedef struct {
//   enum vc_node_type type;
//   union {
//     struct vc_op_node *n;
//     struct vc_value_node *v;
//   } node;
// } vc_ast_node_t;


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

void vc_node_print(vc_ast_node_t *ast) {
  if (ast->type == VC_VALUE_NODE) {
    printf("value:\n");
  } else if (ast->type == VC_VAR_NODE) {
    printf("variable:\n");
  }
}

// vc_ast_node_t *new_vc_ast_node(enum vc_node_type type, vc_ast_node_t *left,
//                                vc_ast_node_t *right) {
//   vc_ast_node_t *node = (vc_ast_node_t *)malloc(sizeof(vc_ast_node_t));
//   node->type = type;
//   node->left = left;
//   node->right = right;
//   return node;
// }

// vc_ast_node_t ast_node = (vc_ast_node_t *)malloc(sizeof(vc_ast_node_t));
// ast_node->

// vc_ast_node_t *
// new_vc_ast_node(enum vc_op op, vc_ast_node_t *left, vc_ast_node_t *right) {
//   vc_ast_node_t *node = (vc_ast_node_t *)malloc(sizeof(vc_ast_node_t));
//   node->node_type = op;
//   node->left = left;
//   node->right = right;
//   return node;
// }
//
// vc_ast_node_t *new_vc_ast_node(enum vc_op op, vc_ast_node_t *left,
//                                vc_ast_node_t *right) {
//   vc_ast_node_t *node = (vc_ast_node_t *)malloc(sizeof(vc_ast_node_t));
//   node->node_type = op;
//   node->left = left;
//   node->right = right;
//   return node;
// }
