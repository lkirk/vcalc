%{
#include "ast.h"

// include the parser last
#include "parser.h"
%}

/* sym     [!-/:-?_\{-~] */
anum    [a-zA-Z_]+
plus    \+
minus   \-
equals  =
digit   [0-9]
real    ({digit}+[.]{digit}*)|({digit}*[.]{digit}+)
integer {digit}+
exp     ({integer}|{real})[eE]-?{integer}
open_bracket \[
close_bracket \]
open_paren \(
close_paren \)

%%
{plus} { return PLUS; }
{minus} { return MINUS; }
{equals} { return EQUALS; }

({real}|{exp}) {
    yylval.fval = atof(yytext);
    return FLOAT;
}

{digit}+ {
    yylval.ival = atoi(yytext);
    return INT;
}

<str>\" /* eat string characters */
<str>\" {
    yylval.sval = yytext;
    return STRING;
}

{anum} {
    yylval.sval = yytext;
    return STRING;
}

{open_bracket} { return L_BRACKET; }
{close_bracket} { return R_BRACKET; }
{open_paren} { return L_PAREN; }
{close_paren} { return R_PAREN; }

[ \t\r\n]+ /* skip blanks */

. {
    yylval.sval = yytext;
    return UNKNOWN;
}
%%
