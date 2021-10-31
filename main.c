#include "ast.h"
#include "parser.h"
#include "khash.h"

#include <stdio.h>
#include <string.h>

int main() {
  vc_scope_t *global_scope = vc_scope_init();
  yyparse(global_scope);
}
