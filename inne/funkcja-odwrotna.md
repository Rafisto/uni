### Teoria

[Funkcja odwrotna](https://en.wikipedia.org/wiki/Inverse_function) $f^{-1}(x)$ do funkcji $f(x)$ spełnia warunek: 

$$
f^{-1}(f(x))=x
$$

### Zadania
  
I. Rozwiąż $f(x)=\frac{x+1}{x-1}$:
Dziedzina funkcji $f(x)$ to $x\neq1$. Następnie:

$$y=\frac{x+1}{x-1}$$

$$(x-1)y=x+1$$

$$xy-y=x+1$$

$$xy-x=y+1$$

$$x(y-1)=y+1$$

$$x=\frac{y+1}{y-1}$$

Zatem $f^{-1}(x)=\frac{x+1}{x-1}$. Sprawdźmy to stosując definicję funkcji odwrotnej:

$$
f^{-1}(f(x))=\frac{f(x)+1}{f(x)-1}=\frac{\frac{x+1}{x-1}+1}{\frac{x+1}{x-1}-1}=\frac{\frac{x+1+1(x-1)}{x-1}}{\frac{x+1-(x-1)}{x-1}}=\frac{\frac{x+1+x-1}{x-1}}{\frac{x+1-x+1}{x-1}}=\frac{\frac{2x}{x-1}}{\frac{2}{x-1}}=x_\blacksquare
$$

II. Rozwiąż $f(x)=3-\sqrt{4-x^2}$:
Dziedzina funkcji $f(x)$ to:

$$4-x^2\geq0$$

$$x^2\leq4$$

$$-2\leq x\leq2$$

Następnie:

$$y=3-\sqrt{4-x^2}$$

$$y-3 = -\sqrt{4-x^2}$$

$$(y-3)^2 = 4-x^2$$

$$y^2 - 6y + 9 = 4 - x^2$$

$$x^2 = -y^2 + 6y - 5$$

$$x = ±\sqrt{-y^2 + 6y - 5}$$

Zatem $f^{-1}(x)=±\sqrt{-x^2 + 6x - 5}$. Sprawdźmy to:

$$f^{-1}(f(x))=$$

$$±\sqrt{-f(x)^2+6f(x)-5}= $$

$$±\sqrt{-\left(3-\sqrt{4-x^2}\right)^2+6\left(3-\sqrt{4-x^2}\right)-5}=$$

$$±\sqrt{-\left(9-6\sqrt{4-x^2}+4-x^2\right)+18-6\sqrt{4-x^2}-5}=$$

$$±\sqrt{-9+6\sqrt{4-x^2}-4+x^2+18-6\sqrt{4-x^2}-5}=$$

$$±\sqrt{x^2-9-4-5+18}=$$

$$±\sqrt{x^2}=±|x|$$

Całość zachodzi ponieważ rozważając 2 przypadki $x\in[-2,0]$ oraz $x\in[0,2]$ otrzymujemy $f^{-1}(f(x))=x$. 

Polecenia operacji do [wolframalpha](https://www.wolframalpha.com):
1. `find inverse of f(x)=(x+1)/(x-1)`
2. `find inverse of f(x)=3-sqrt(4-x^2)`
