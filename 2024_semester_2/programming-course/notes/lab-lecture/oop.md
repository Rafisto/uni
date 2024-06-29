## OPEN-CLOSE

Zasada otwartości na nowe funcjonalości, zamkniętość na modyfikacje kodu.

Dziedziczenie

Interfejs

```java
int[] findDup(int[] arr) {
    //mergeSort(arr);
    dualPivotQuickSort(arr);
}
```

```
IN: 1 2 3 2 4 1 2 O(n^2)
OUT: [1,2]

SORT: 1 1 2 2 3 4 O(n log n + n)
OUT: [1, 2]
```

Historia
```
1985: quick sort (Cedwick)
2011: double pivot quick sort (Yaroslavski)
```

Interfejs

```java
Interface Sort {
    sort(int[] arr);
}

class MergeSort implements Sort {
    sort(int[] arr) {
        mergeSort(arr);
    }
}

class QuickSort implements Sort {
    sort(int[] arr) {
        quickSort(arr);
    }
}

// i teraz

int[] findDup(int[] arr, Sort s) {
    s.sort(arr);
}
```

Override

```java
class X {
    print() {
        print("Ala");
    }
}

super(1,2);
super.print();
```

```java
// an interesting debug method
class Y extends X {
    @override
    print() {
        super.print();
        print("Ola");
    }
}
```

Full change

```java
class Y extends X {
    @override
    add(x,y) {
        x-y;
    }
}
```

### Worst-ever code example

> Dokładamy kolejne gówno, aż wyjdzie sułtańskie gówno ~ Kukos

```java
class AFigure {
    abstract double area(double[] sides);
}

class Rectangle extends AFigure {
    double x;
    double y;

    Rectangle(x,y) {
        x = x;
        y = y;
    }

    @override
    double area(double[] sides) {
        return sides[0] * sides[1];
    }
}

Rect r = new Rect(1,2);
print(r.area(new[]{1,2}));
```

### Better code example

```java 
class AFigure {
    abstract double area();
}

class Rectangle extends AFigure {
    double x;
    double y;

    Rectangle(x,y) {
        x = x;
        y = y;
    }

    @override
    double area() {
        return x * y;
    }

    double getX() {
        return x;
    }

    double getY() {
        return y;
    }
}

class Sqaure extends AFigure {
    double x;

    Sqaure(x) {
        x = x;
    }

    @override
    double area() {
        return x * x;
    }
}
```

```java
if (square) {
    Square = new Square();
} else if (rectangle) {
    Rectangle = new Rectangle();
}
```

Dziedziczenie dynamiczne - polimorfizm

```java
Rect v = new Rect();
v.area();
v.getX();
v.getY();

// no longer a rectangle, just a figure
AFigure v = new Rect();
v.area();
v.getX(); // error

// pros don't use instanceof operator
if(v instanceof Rect) {
    v.getX();
}
// because this shit will happen shortly after
else if(v instanceof Square) {
    v.getX();
}

// instanceof can be used with instances
```

Nie ma multidziedziczenia klas w java, ale jest dla interfejsów.
```java
if (k instanceof K) {
    print("Ala");
}

interface IX;

class X implements IX {};
class Y extends AFigure implements IFig, IX {};
```

C++ - Klasy abstrakcyjne jako interfejsy, unikamy multidziedziczenia
```c++
abstract/virtual
```

Nie zmieniamy klas - załamanie feng-shui. Wymusza to nowe:
- test_case-y
- czytanie kodu
- funkcjonalności

> DRY - don't repeat yourself

```java
ArrayList<AFigure> figures = new ArrayList();

if (square) 
    figures.add(new Square())
else if(rectangle)
    figures.add(new Rectangle())

for (AFigure f : figures) {
    p(f.area());
}
```

vTable<br/>

Do poczytania: 
[Zasada zera, trzech, pięciu](https://en.cppreference.com/w/cpp/language/rule_of_three)

Specyfikacja

```java
class Button {
    Button(Color c, Size s, Fg f, Bg b) {

    }
} 

class onClick(Button) {
    ...
}

class MyButton extends Button {
    MyButton() {
        super(Color.RED, Size.MEDIUM, Fg.BLACK, Bg.WHITE);
    }
}
```

```java
class X {
    abstract foo(int x);
    bar(int x) {return x;}
}

class Y extends X {
    @override
    foo(int x) {
        return x; // fine
    }

    @override
    bar(int x) {
        return x; // fine
    }
    // can always override
}
```

```c++
class X {
    virtual foo(int x) = 0; // can override, pure virtual - requires an implementation
    bar(int x) {return x;} // can't override
}

class Y : public X {
    virtual foo(int x) override {
        return x; // fine
    }
    bar(int x) {
        return x; // error - can't override
    }
}
```

performance:
- final -> jvm = nice
- w/o final -> jvm = not nice

c++:
- 0 abstraction cost - no performance loss
    - no try-catch, virtual