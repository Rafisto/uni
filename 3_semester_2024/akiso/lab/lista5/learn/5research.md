

```plaintext
x2:= 0
y2:= 0

while (x2 + y2 ≤ 4 and iteration < max_iteration) do
    y:= 2 * x * y + y0
    x:= x2 - y2 + x0
    x2:= x * x
    y2:= y * y
    iteration:= iteration + 1
```

target remote localhost:1234
symbol-file boot.elf