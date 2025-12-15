/* - delete white space at beginning and end of a row */
/* - replace all sequences of tabs and spaces with a single space */
/* - delete empty lines */
/* - count number of lines and words */
%{
#include <stdio.h>
    int yywrap();
    int yylex();
    int WC = 0;
    int WL = 0;
%}
%%
^[[:blank:]]*(\n)*
[[:blank:]]+$
[[:blank:]]+ { printf(" "); }
[^ \t\n]+ { ECHO; WC++; }
^\n
\n { printf("\n"); WL++; }
%%
int yywrap() {
    printf("---\nWords=%d", WC);
    printf("\nLines=%d\n", WL);
    return 1;
}

int main() { 
    return yylex();    
}
