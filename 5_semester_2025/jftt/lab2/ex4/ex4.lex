/* Simple Postfix calculator */
%option noyywrap
%{
    #include <stdio.h>
    #include <stack>
    #include <cmath>
    #include <string>
    int yylex();
    double a, b;
    std::stack<double> n;
%}
%x error
%%
\-?[0-9]+ { n.push(atoi(yytext)); }

"+"|"-"|"*"|"/"|"^"|"%" {
    if (n.size() > 1) {
        b = n.top();
        n.pop();
        a = n.top(); 
        n.pop();
        if (b==0 && strcmp(yytext, "/")==0) {
            printf("\rZero-division error attempting %g/%g\n", a, b);
            n = std::stack<double>();
            BEGIN(error);
        }
        REJECT;
    }
    else {
        printf("\rInvalid number of operands for binary operator\n");
        n = std::stack<double>();
        BEGIN(error);
        REJECT;
    }
}

"+" { n.push(a + b); }
"-" { n.push(a - b); }
"*" { n.push(a * b); }
"/" { n.push(a / b); }
"^" { n.push(pow(a,b)); }
"%" { n.push((int)a % (int)b); }

^\n

\n {
    if (n.size() > 1) {
        printf("\rBad number of operands, stack size %zu !> 1\n", n.size());
        n = std::stack<double>();
    }
    else if (n.size() == 1) {
        printf("\r= %g\n", n.top());
        n.pop();
    }
}

[^0-9\+\-\*\^/%\n ] {
    printf("\rInvalid character '%s'\n", yytext);
    n = std::stack<double>();
    BEGIN(error);
}

<error>{
    .*\n { n = std::stack<double>(); BEGIN(INITIAL); }
}
%%

int main() {
    yylex();
}
