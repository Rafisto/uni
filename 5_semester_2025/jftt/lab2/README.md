```bash
pacman -S flex
```

- C line directive
- R"fmt(string)fmt" string literals in C++

```bash
# ex1
diff <(cat ./tests/test.txt | ./a.out) <(cat ./tests/test.res.txt)
# ex2
diff <(cat ./tests/test.py | ./a.out) <(cat ./tests/test.res.py)
# ex3
diff <(cat ./tests/test.cpp | ./a.out) <(cat ./tests/test.res.cpp)
diff <(cat ./tests/test.cpp | ./a.out --keep-doxygen) <(cat ./tests/test.res.doxygen.cpp)
# ex4
diff <(cat ./tests/input | ./a.out) <(cat ./tests/output)
```