#include "ast.h"
#include "parser.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  yyparse();
}