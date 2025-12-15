## Clang Format

```bash
find . -name "*.[ch]pp" -exec clang-format -i {} \;
for i in $(find . -type d | grep -v tests); do cd $i && make test && cd ..; done
```