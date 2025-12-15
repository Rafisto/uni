## Bison

A parser which converts context-free grammars into a deterministic LR (left-to-right) parser.
- Install bison - https://archlinux.org/packages/core/x86_64/bison/
- Read user manual - https://www.gnu.org/software/bison/manual/

```bash
sudo pacman -S bison
```

Any Grammar written in Backus-Naur Form is a context-free grammar.
- Token: piece corresponding to a single terminal symbol
- Grouping: piece corresponding to a single nonterminal symbol

Convention:
- Nonterminals are lowercase
- Terminals are uppercase, most likely the uppercase form of a token.

When the parser accepts the token, it keeps track of the token’s **semantic value**. 

Location of the whole grouping is @$, while the locations of the subexpressions are @1 and @3. 

```bash
flex -o lex.yy.cpp rpcalc.lex
bison -d rpcalc.yy 
clang++ -o rpcalc rpcalc.tab.cc lex.yy.cpp --std=c++23
```