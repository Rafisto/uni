```bash
make
./buchberger.out | sed "s/0\+/0/g"
```

Wolfram

```bash
GrobnerBasis({}) 


Geogebra (d)


```bash
echo "(y^4.0) + 4.80(y^3.0)(z) + 1.60(y^3.0) + 9.160(y^2.0)(z^2.0) + 6.240(y^2.0)(z) + 0.640(y^2.0) + 8.160(y)(z^3.0) + 8.640(y)(z^2.0) + 1.920(y)(z) + 2.880(z^4.0) + 4.320(z^3.0) + 1.440(z^2.0)" | sed "s/y/x/g" | sed "s/z/y/g"
```

Geogebra (e)

```text
b = 7
f(x) = 7 *(4 * cos (x) + 1/(cos(x)))
Curve(f(t) * cos(t), f(t) * sin(t), t, 0, 2 * pi)
```