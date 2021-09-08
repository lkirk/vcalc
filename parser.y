%{
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

extern void yyerror();
extern int yylex();
%}

%define parse.error verbose

%union
{
    int ival;
    double fval;
    char *sval;
    vc_ast_node_t *node;
}

%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%token EQUALS
/* %token <node> NODE */
%token UNKNOWN

/* %left '<' '>' '=' "!=" "<=" ">=" */
%left PLUS MINUS
/* %left '*' '/' */

/* %right UMINUS */
/* %left L_BRACKET R_BRACKET */
%token L_BRACKET R_BRACKET
%token L_PAREN R_PAREN

%%
/* program:
       %empty
       | program line

line:
    '\n'
    | expressions '\n'

expressions:
           expression
           | expressions expression
*/

program:
    %empty
    | program line

expressions:
           expression
           | expressions expression

line:
    '\n'
    | expressions expression '\n'

expression:
          value
          | value PLUS value { $<node>$ = new_vc_op_node(VC_ADD, $<node>1, $<node>3); }
          | value EQUALS value {
              if ($<node>1->type == VC_VAR_NODE) {
                  printf("ASSIGNMENT\n");
              }
          }
          | L_PAREN expression R_PAREN

value:
     INT { vc_value_t val; val.i = $<ival>1; $<node>$ = new_vc_value_node(VC_INT, val); }
     | FLOAT { vc_value_t val; val.i = $<ival>1; $<node>$ = new_vc_value_node(VC_FLOAT, val); }
     | STRING { $<node>$ = new_vc_variable_node($<sval>1, NULL); }
%%
