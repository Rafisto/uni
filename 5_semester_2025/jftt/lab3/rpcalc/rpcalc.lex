%{
    #include <print>
    #include "rpcalc.tab.hh"
    int yylex(void);
%}

%option noyywrap

%%

[ \t]+;
\-?[0-9]+("."[0-9]+)* { yylval = std::stod(yytext); return NUM; }
\n { return NL; }
"+" { return PLU; }
"-" { return MIN; }
"*" { return MUL; }
"/" { return DIV; }
"^" { return POW; }
%%
