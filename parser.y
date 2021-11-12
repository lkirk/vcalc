%{
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

extern void yyerror();
extern int yylex();
%}

%define parse.error verbose

%parse-param {vc_scope_t *scope}


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

program:
    %empty
    | program line

expressions:
           expression
           | expressions expression
           | L_PAREN expression R_PAREN

line:
    '\n'
    | expressions expression '\n'

expression:
          value
          | value PLUS value { $<node>$ = new_vc_op_node(VC_ADD, $<node>1, $<node>3); }
          | STRING EQUALS value { $<node>$ = new_vc_variable_node($<sval>1, $<node>3->node.v); }

value:
     INT { vc_value_t val; val.i = $<ival>1; $<node>$ = new_vc_value_node(VC_INT, val); }
     | FLOAT { vc_value_t val; val.f = $<fval>1; $<node>$ = new_vc_value_node(VC_FLOAT, val); }
     | STRING { vc_value_t val; val.s = $<sval>1; $<node>$ = new_vc_value_node(VC_STR, val); }
     | UNKNOWN { yyerror("ERROR: unknown token"); }
%%
