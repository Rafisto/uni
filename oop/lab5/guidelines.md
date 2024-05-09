## Menu

1. FILE
- save
- load
2. INFO
3. MODE square, circle, triangle

## Figures

LPM:
- figure
    - SELECT: active
- no figure
    - event
        - MODE VISUAL: none
        - MODE square circle triangle: add point

## Open issues

Rozwiązuje jakkolwiek mi się podoba:
- Co jeśli kliknę circle a potem figure na panelu?
- Jak rysować? - minimalnie dwa punkty (square, circle), 3 punkty (triangle)
- Skalowanie - scroll
- Sposób obracania? - CTRL + scroll, CTRL + LPM + onHold
- Jak pokazać isActive? - do outline
- Jak zrobić save i load? - użyć serialize, nie robić swojego
- Jedno ~~z dwóch ale~~ doxygen
- Jak traktować Layers? - zostawić jak było, przenieść na foreground
- Resize `=` scale
- Figury mają być pełne w środku

## Open close
Aby móc dodać kolejne figury bez zmiany kodu

Fatalny kod:
```
biguglyfunc(...){
    if (mode == 1)
    {

    }
    else if(mode == 2)
    {

    }
}
```

Wybranie funkcjonalności
```
mechanizm -> (state machine)
```

Dobry kod:
```
class rect, tri, circ :: javafx.Shape
class my_rect, my_tri, my_circ implements IFigure
// create interface
IFigure {
    scale,
    move,
    rotate
}
IFigureGUI {
    color,
    outline
}
instanceof na interfejsie ok
instanceof na klasie nie ok

GUI:
Drawer d;
= [sq] Sq Drawer;
= [ci] Circl Drawer
= [tri] Tri Drawer
```

```
I - option
LPM - d.addPoint(...)
if d.isready() {
    javafx.Shape s = d.build()
    draw(s)
}
II - option
LPM handled by drawer
```