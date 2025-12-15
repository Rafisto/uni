/* https://westes.github.io/flex/manual/Start-Conditions.html */
/* Deletes all C++98 comments and keeps Doxygen ones if requested */
/* https://www.doxygen.nl/manual/docblocks.html */
%option noyywrap
%{
  #include <stdio.h>
  #include <stdbool.h>
  #include <string.h>

  int yylex();
  bool keep_doxygen = false;
%}

%x sq_string
%x dq_string
%x d_comment_multi
%x comment_multi
%x comment_single
%x d_comment_single

%%
<INITIAL>{
    (\n|\t|" ")*("/**"|"/*!")([^\n]*)"*/" { if (keep_doxygen) ECHO; }
    (\n|\t|" ")*"/*"([^\n]*)"*/" { }
    
    \"              { ECHO; BEGIN(dq_string); }
    \'              { ECHO; BEGIN(sq_string); }

    (\n|\t|" ")*("/**"|"/*!") {
        if (keep_doxygen) { ECHO;; BEGIN(d_comment_multi); }
        else { BEGIN(comment_multi); }
    }

    (\n|\t|" ")*("///"|"//!") {
        if (keep_doxygen) { ECHO; BEGIN(d_comment_single); }
        else { BEGIN(comment_single); }
    }

    (\n|\t|" ")*"/"(\\\n)*"*" {
        BEGIN(comment_multi);
    }

    (\n|\t|" ")*"/"(\\\n)*"/"[^/!] {
        BEGIN(comment_single);
    }

    .             { ECHO; }
}

<dq_string>{
    \\(.)           { ECHO; }
    \"              { ECHO; BEGIN(INITIAL); }
    [^\\"]+         { ECHO; }
}

<sq_string>{
    \\(.)           { ECHO; }
    \'              { ECHO; BEGIN(INITIAL); }
    [^\\']+         { ECHO; }
}

<comment_single>{
    .|\\\n
    [^\\]\n         { printf("\n"); BEGIN(INITIAL); }
}

<comment_multi>{
    "*/"                  { BEGIN(INITIAL); } 
    \n
    .|\\\n
}

<d_comment_single>{
    .|\\\n          { if (keep_doxygen) ECHO; }
    \n              { ECHO; BEGIN(INITIAL); }
}

<d_comment_multi>{
    "*/" { if (keep_doxygen) ECHO; BEGIN(INITIAL); }
    \n { if (keep_doxygen) ECHO; }
    .|\\\n { if (keep_doxygen) ECHO; }
}
%%
int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--keep-doxygen") == 0)
        keep_doxygen = true;

    if (keep_doxygen) fprintf(stderr, "Doxygen comments will be preserved.\n");

    yylex();
    return 0;
}
