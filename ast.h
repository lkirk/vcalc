#pragma once

#include <stdint.h>

#include "khash.h"

enum vc_op { VC_ADD, VC_SUB, VC_DIV, VC_MULT, VC_EXP };
enum vc_value { VC_INT, VC_FLOAT };
enum vc_node_type { VC_VALUE_NODE, VC_OP_NODE, VC_VAR_NODE };

typedef struct vc_ast_node {
  enum vc_node_type type;
  union {
    struct vc_op_node *n;    // TODO: op
    struct vc_value_node *v; // TODO: val
    struct vc_var_node *var;
  } node;
} vc_ast_node_t;

typedef union vc_value_obj {
  float f;
  uint64_t i;
  const char *s;
} vc_value_t;

typedef struct vc_value_node {
  enum vc_value value_type;
  vc_value_t value;
} vc_value_node_t;

KHASH_MAP_INIT_STR(str_to_vc_value, vc_value_node_t)
typedef khash_t(str_to_vc_value) vc_scope_t;

typedef struct vc_op_node {
  enum vc_op op;
  vc_ast_node_t *left;
  vc_ast_node_t *right;
} vc_op_node_t;

typedef struct vc_var_node {
  const char *name;
  vc_value_node_t *value;
} vc_var_node_t;

vc_ast_node_t *new_vc_op_node(enum vc_op op, vc_ast_node_t *left,
                              vc_ast_node_t *right);
vc_ast_node_t *new_vc_value_node(enum vc_value value_type, vc_value_t value);
vc_ast_node_t *new_vc_variable_node(const char *name, vc_value_node_t *value);

vc_scope_t *vc_scope_init();
void vc_scope_put(vc_scope_t *scope, const char *key, vc_value_node_t *val);
vc_value_node_t *vc_scope_get(vc_scope_t *scope, const char *key);
