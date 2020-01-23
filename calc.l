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
//yylval_t yylval;
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

PUNCTUATION         [-();+*/=]|"["|"]"
VAR                 [a-zA-Z][a-zA-Z0-9]*
NUM                 [0-9]+
WHITESPACE          [ \t\n]+
JUNK                .

%%

    // stuff goes here.

{PUNCTUATION}           DO_RETURN(yytext[0]);

"while"                 DO_RETURN(WHILE);
"end"                   DO_RETURN(END);

{VAR}                   DO_RETURN(VAR);
{NUM}                   DO_RETURN(NUM);

{WHITESPACE}            {}

{JUNK}                  {}

%%
// function definitions go here.
