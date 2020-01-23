%{
//*************************************************
// calc.l
// 
// Scanner for lab03 of compilers class
//
// Author: Noah Shorter
// noah.shorter@oit.edu
//
// Date: Jan. 22, 2020
//
//*************************************************

#include "tokens.h"
#include "lex.h"

#define DO_RETURN(a) return (a)

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

PUNCTUATION         [();]|"["|"]"
OP                  [+-*/]
VAR                 [a-zA-Z][a-zA-Z0-9]*
NUM                 [0-9]+
WHITESPACE          [ \t\n]+

%%

{PUNCTUATION}           DO_RETURN(yytext[0]);
{OP}                    DO_RETURN(yytext[0]); // + = 43, - = 45, * = 42, / = 47

"while"                 DO_RETURN(WHILE);

{VAR}                   DO_RETURN(VAR);
{NUM}                   DO_RETURN(NUM);

{WHITESPACE}            {}

%%
// function definitions go here.
