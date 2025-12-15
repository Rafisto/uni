%{
    #include <print>
    #include <optional>
    #include <string>
    #include <queue>
    #include <cmath>

    int yylex(void);
    void yyerror(char const*);
    int yyparse();

    long gf_min(long a, long M);

    #define N 1234577
    #define S(x) std::to_string(x)

    std::queue<std::string> ops;
    std::optional<std::string> error;

    void clearq(std::queue<std::string>& q) {
      std::queue<std::string> empty;
      std::swap(q, empty);
    }

    void skip() {
      clearq(ops);  
      error.reset();
    }

    void result(long r) {
      if (not error) {
        while (ops.size()) {
          std::string first = ops.front();
          ops.pop();
          if (!ops.empty()) {
            std::string second = ops.front();
            if (second == "u") {
              std::print("{} ", gf_min(std::stol(first), N));
              ops.pop();
              continue;
            }
            else if (second == "v") {
              std::print("{} ", gf_min(std::stol(first), N-1));
              ops.pop();
              continue;
            }
          }
          std::print("{} ", first);
        }
        std::println("\nResult: {}", r);
        return;
      }

      std::println("Error: {}", *error);
      clearq(ops);
      error.reset(); 
    }

    void push(const std::string& s) {
        ops.push(s);
    }

    long gf_mod(long a, long M) {
      return ((a + M) % M);
    }

    long gf_add(long a, long b, long M) {
      return ((a % M) + (b % M)) % M;
    }
    
    long gf_sub(long a, long b, long M) {
      if (a >= b) return ((a % M) - (b % M));
      else return (M - ((b % M) - (a % M)));
    }

    long gf_mul(long a, long b, long M) {
      return ((a % M) * (b % M)) % M;
    }

    long gf_min(long a, long M) {
      return (M - (a % M)) % M;
    }

    long gf_inv(long a, long M) {
      long b = M, u = 1, v = 0;
      while (b != 0) {
          long t = a / b;
          long tmp = a - t * b; a = b; b = tmp;
          tmp = u - t * v; u = v; v = tmp;
      }
      if (u < 0) u += M;
      return u;
    }
    
    long gf_div(long a, long b, long M) {
      if (b == 0) { 
        error = "zero-division error";
        return 0;
      }
      return gf_mul(a, gf_inv(b, M), M);
    }

    bool coprime(long a, long b) {
      while (b != 0) {
        long t = a % b;
        a = b;
        b = t;
      }
      return a == 1;
    }

    long gf_pow(long b, long exp, long M) {
      long res = 1;
      b = gf_mod(b, M);
      while (exp > 0) {
        if (exp % 2 == 1) {
          res = gf_mul(res, b, M);
        }
        b = gf_mul(b, b, M);
        exp /= 2;
      }
      return res;
    }

    long r_div(long a, long b, long M) {
      if (not coprime(b,M)) {
        error = "no inverse exist in ring";
        return 0;
      }
      else return gf_div(a,b,M);
    }
%}

%require "3.2"
%define api.value.type {long}

%token NUM
%token LPAREN
%token RPAREN
%left ADD SUB
%left MUL DIV
%right POW
%right NEG
%token NL
%token ERR

%%

input: %empty | input line;

line: NL | expr NL { result($1); } | error NL { skip(); };

expr: ERR                  { error = "invalid token"; } |
      NUM                  { $$ = gf_mod($1,N);    push(S(gf_mod($1,N)));  } |
    expr ADD expr          { $$ = gf_add($1,$3,N); push("+");              } |
    expr SUB expr          { $$ = gf_sub($1,$3,N); push("-");              } |
    expr MUL expr          { $$ = gf_mul($1,$3,N); push("*");              } |
    expr DIV expr          { $$ = gf_div($1,$3,N); push("/");              } |
    expr POW pow_expr      { $$ = gf_pow($1,$3,N); push("^");              } |
    SUB expr %prec NEG     { $$ = gf_min($2,N);    push("u");              } |
    LPAREN expr RPAREN     { $$ = $2;                                      };

pow_expr: NUM              { $$ = gf_mod($1,N-1);    push(S(gf_mod($1,N))); } |
    pow_expr ADD pow_expr  { $$ = gf_add($1,$3,N-1); push("+");             } |
    pow_expr SUB pow_expr  { $$ = gf_sub($1,$3,N-1); push("-");             } |
    pow_expr MUL pow_expr  { $$ = gf_mul($1,$3,N-1); push("*");             } |
    pow_expr DIV pow_expr  { $$ = r_div($1,$3,N-1);  push("/");             } |
    SUB pow_expr %prec NEG { $$ = gf_min($2,N-1);    push("v");             } |
    LPAREN pow_expr RPAREN { $$ = $2;                                       };
%%

void yyerror (char const *s)
{
  std::print("Error: input error\n", s);
}

int main (void)
{
  return yyparse();
}
