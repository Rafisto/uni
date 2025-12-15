import ply.lex as lex
import ply.yacc as yacc
from collections import deque

# % globals %

N = 1234577
ops: deque = deque()
error = None

# % helpers %

def clearq(q):
    q.clear()

def skip():
    global error
    clearq(ops)
    error = None

def push(s: str):
    ops.append(s)

# % math %

def gf_mod(a, M):
    return (a + M) % M

def gf_add(a, b, M):
    return ((a % M) + (b % M)) % M

def gf_sub(a, b, M):
    if a >= b:
        return ((a % M) - (b % M))
    else:
        return M - ((b % M) - (a % M))

def gf_mul(a, b, M):
    return ((a % M) * (b % M)) % M

def gf_min(a, M):
    return (M - (a % M)) % M

def gf_inv(a, M):
    b, u, v = M, 1, 0
    while b != 0:
        t = a // b
        a, b = b, a - t * b
        u, v = v, u - t * v
    if u < 0:
        u += M
    return u

def gf_div(a, b, M):
    if b == 0:
        global error
        error = "zero-division error"
        return 0
    return gf_mul(a, gf_inv(b, M), M)

def gf_pow(base, exp, M):
    res = 1
    base = gf_mod(base, M)
    while exp > 0:
        if exp % 2 == 1:
            res = gf_mul(res, base, M)
        base = gf_mul(base, base, M)
        exp = exp // 2
    return res

def coprime(a, b):
    while b:
        a, b = b, a % b
    return a == 1

def r_div(a, b, M):
    global error
    if not coprime(b, M):
        error = "no inverse exist in ring"
        return 0
    return gf_div(a, b, M)

# % result %

def result(r):
    global error, ops

    if error is None:
        while ops:
            first = ops.popleft()

            if ops:
                second = ops[0]
                if second == "u":
                    print(gf_min(int(first), N), end=" ")
                    ops.popleft()
                    continue
                elif second == "v":
                    print(gf_min(int(first), N-1), end=" ")
                    ops.popleft()
                    continue

            print(first, end=" ")

        print(f"\nResult: {r}")
        return

    print(f"Error: {error}")
    clearq(ops)
    error = None

# % lexer %

tokens = (
    "NUM",
    "LPAREN",
    "RPAREN",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "POW",
    "NL",
    "ERR",
)

t_LPAREN = r"\("
t_RPAREN = r"\)"
t_ADD    = r"\+"
t_SUB    = r"-"
t_MUL    = r"\*"
t_DIV    = r"/"
t_POW    = r"\^"
t_ignore = " \t"

def t_COMMENT(t):
    r"\#[^\n]*"
    pass

def t_LINECONT(t):
    r"\\\n"
    pass

def t_NUM(t):
    r"[0-9]+"
    t.value = int(t.value)
    return t

def t_ERR(t):
    r"[0-9A-Za-z]+"
    return t

def t_NL(t):
    r"\n"
    return t

def t_error(t):
    t.type = "ERR"
    t.value = t.value[0]
    t.lexer.skip(1)
    return t

lexer = lex.lex()

# % parser %

precedence = (
    ("left", "ADD", "SUB"),
    ("left", "MUL", "DIV"),
    ("right", "POW"),
    ('right', "NEG"),
)

def p_input_empty(p):
    "input : "
    pass

def p_input_recursive(p):
    "input : input line"
    pass

def p_line_nl(p):
    "line : NL"
    pass

def p_line_expr(p):
    "line : expr NL"
    result(p[1])

def p_line_error(p):
    "line : error NL"
    skip()

def p_expr_err(p):
    "expr : ERR"
    global error
    error = "input error"
    p[0] = 0
    pass

def p_expr_num(p):
    "expr : NUM"
    v = gf_mod(p[1], N)
    push(str(v))
    p[0] = v

def p_expr_add(p):
    "expr : expr ADD expr"
    push("+")
    p[0] = gf_add(p[1], p[3], N)

def p_expr_sub(p):
    "expr : expr SUB expr"
    push("-")
    p[0] = gf_sub(p[1], p[3], N)

def p_expr_mul(p):
    "expr : expr MUL expr"
    push("*")
    p[0] = gf_mul(p[1], p[3], N)

def p_expr_div(p):
    "expr : expr DIV expr"
    push("/")
    p[0] = gf_div(p[1], p[3], N)

def p_expr_pow(p):
    "expr : expr POW pow_expr"
    push("^")
    p[0] = gf_pow(p[1], p[3], N)

def p_expr_unary(p):
    "expr : SUB expr %prec NEG"
    push("u")
    p[0] = gf_min(p[2], N)

def p_expr_paren(p):
    "expr : LPAREN expr RPAREN"
    p[0] = p[2]

# power ring expr

def p_pow_num(p):
    "pow_expr : NUM"
    v = gf_mod(p[1], N-1)
    push(str(v))
    p[0] = v

def p_pow_add(p):
    "pow_expr : pow_expr ADD pow_expr"
    push("+")
    p[0] = gf_add(p[1], p[3], N-1)

def p_pow_sub(p):
    "pow_expr : pow_expr SUB pow_expr"
    push("-")
    p[0] = gf_sub(p[1], p[3], N-1)

def p_pow_mul(p):
    "pow_expr : pow_expr MUL pow_expr"
    push("*")
    p[0] = gf_mul(p[1], p[3], N-1)

def p_pow_div(p):
    "pow_expr : pow_expr DIV pow_expr"
    push("/")
    p[0] = r_div(p[1], p[3], N-1)

def p_pow_unary(p):
    "pow_expr : SUB pow_expr %prec NEG"
    push("v")
    p[0] = gf_min(p[2], N-1)

def p_pow_paren(p):
    "pow_expr : LPAREN pow_expr RPAREN"
    p[0] = p[2]

def p_error(p):
    print("Error: input error")

parser = yacc.yacc()

# % main %

if __name__ == "__main__":
    import sys

    try:
        while True:
            try:
                line = input("> ")
            except EOFError:
                print()
                break

            if line.strip() == "":
                continue

            parser.parse(line + "\n")

    except KeyboardInterrupt:
        print("\nExiting.")
        sys.exit(0)