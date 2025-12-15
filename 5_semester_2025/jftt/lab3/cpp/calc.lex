%{
    #include <print>
    #include "calc.tab.hh"
    int yylex(void);
%}

%option noyywrap

%%
\\\n
#[^\n]*
[ \t]+
[0-9]+ {yylval = std::stol(yytext); return NUM; }
[0-9A-Za-z]+ { return ERR; }
\n { return NL; }
"(" { return LPAREN; }
")" { return RPAREN; }
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"^" { return POW; }
. { return ERR; }
%%
