/* https://westes.github.io/flex/manual/Start-Conditions.html */
/* - delete all python comments as stated in https://docs.python.org/3/reference/lexical_analysis.html#comments */
%{
#include <stdio.h>
    int yywrap();
    int yylex();
%}

%x sq_t_string
%x dq_t_string
%x sq_string
%x dq_string

%%
<INITIAL>{
    \\\" { printf("\\\""); }
    \\\' { printf("\\\'"); }
    \'\'\' { printf("\'\'\'"); BEGIN(sq_t_string); }
    \"\"\" { printf("\"\"\""); BEGIN(dq_t_string); }
    \' { printf("\'"); BEGIN(sq_string); }
    \" { printf("\""); BEGIN(dq_string); }
    [[:blank:]]*#[^\n]*
    #[^\n]*
    \n { printf("\n"); }
}

<dq_t_string>{
    \\(.|\n)        { ECHO; }           
    \"\"\"          { printf("\"\"\""); BEGIN(INITIAL); }
    [^\\"]+         { ECHO; }
    \"              { ECHO; } 
}

<sq_t_string>{
    \\(.|\n)        { ECHO; }           
    \'\'\'          { printf("\'\'\'"); BEGIN(INITIAL); }
    [^\\']+         { ECHO; }
    \'              { ECHO; } 
}

<dq_string>{
    \\(.)           { ECHO; }
    \"              { printf("\""); BEGIN(INITIAL); }
    [^\\"]+         { ECHO; }
}

<sq_string>{
    \\(.)           { ECHO; }
    \'              { printf("\'"); BEGIN(INITIAL); }
    [^\\']+         { ECHO; }
}

%%
int yywrap() {
    return 1;
}

int main() { 
    return yylex();
}
