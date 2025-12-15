/* simple calc */

%{
    #include <print>
    #include <cmath>
    int yylex(void);
    void yyerror(char const*);
    int yyparse();
%}

%require "3.2"
%define api.value.type {double}

%token NUM
%token PLU
%token MIN
%token MUL
%token DIV
%token POW
%token NL

%%

input: %empty | input line;

line: NL
    | expr NL { std::print("{}\n", $1); }
    ;

expr: NUM |
    expr expr PLU { $$ = $1 + $2; } |
    expr expr MIN { $$ = $1 - $2; } |
    expr expr MUL { $$ = $1 * $2; } |
    expr expr DIV { $$ = $1 / $2; } |
    expr expr POW { $$ = pow($1,$2); };
%%

void yyerror (char const *s)
{
  std::print(stderr, "{}\n", s);
}

int main (void)
{
  return yyparse();
}