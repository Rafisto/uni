### Guidelines dla Listy 7

1. Napisz BST (Binary Search Tree) w c++/java - używając templates
2. Dodaj CLI (Command Line Interface):
    - which tree? `string, int, bool`
    - `i 5` = `a 5` insert 5
    - `r 5` = `d 5` delete 5
    - `s 5` = `f 5` find 5 - is 5 in the tree?
    - `p` print

Przykład funkcji

```c
// wykonywany kod jest taki sam.
f() a+b
g() a+c
h() d+e

// zwinąć w
add(..., ...)


// wykonywany kod jest różny, ale ma te samą sygnaturę
f() {
    addPoint();
    if(ready){
        draw();
    }
}
```

Zaimplementujmy funkcję minimum:
```c
(a <= b) ? a : b // ternary operator, nie ma związku z zadaniem
```

Makra dla Integer:
```c
#define Min(a,b) (a<= b) ? a : b

int c = Min(2,3);
int c = (_ <= _ ) ? _ : _;
int c = (2 <= 3 ) ? 2 : 3;

int c = 2;
```

Problem z wykonywaniem makr:
```c
// bez sensu (I)
int a = 2;
int b = 3;
int c = Min(++a,b);
int c = (++a <= 3) ? ++a : 3;

// bez sensu (II)
int c = Min(a, 'a');
```

Zaimplementujmy funkcję minimum dla int, double
```c
// Generalnie w języku C nie można zdefiniować funkcji o tej samej nazwie 
int min(int,int)
double min(double,double)

#define Min_F(type) type min(type a, type b) { return (a <= b) ? a : b; }

Min_F(int)
Min_F(double)

// stworzy
int min(int a, int b);

// wykorzystanie
int main() {
    int c = min(2,3);
}
```

Stwórzmy template:
```cpp
template <typename T>
T min(T a, T b) {
    return (a <= b) ? a : b;
}

int main() {
    int c = min<int>(2,3);
}
```

Template dla klas:
```cpp
template <typename T>
class c {
    int tab[T];
}

c c<100>();
```

```cpp
constexpr int fib(constexpr int n)
    if (n<2) return n;
    return fib(n-1) + fib(n-2);

// policzy fib(5) w czasie kompilacji
int c = fib(5) ;// -> int c = 5;

// kompilator tego nie ruszy
cin >> n;
fib(n);
```

Przydatne w printowaniu logów (miejsce w kodzie jest ustalane w trakcie kompilacji):
```cpp
"file", ".txt"
std:string("ala");
s.length(); // compiled just in time
s.substring(); // compiled just in time
```

```java
class BST<T> {
    public boolean exists(T value) {
        // implementation
    }
    
    public void insert(T value) {
        // implementation
    }
    // ...
}
```

Stwórzmy templat-eowane nested klasy:
```java
// bez sensu bo Node n<Int> = ...; nieużywalne - Node nie powinno być wystawione
class BST<T>;
class Node<T>;
```

```java
class BST<T> {
    void insert(T value) {

    }
}

// długi i nieprzyjemny kod
BST<Integer> b = new ...
Node<Integer> n = new Node<Integer>(5);
b.insert(n);

// tak byłoby lepiej
BST<Integer> b = new ...
b.insert(5);

// żeby można było tak zrobić to:
// zakładamy że mamy dostęp do nested klasy
class BST<T> {
    public class Node<T> {
        T value;
        Node<T> left;
        Node<T> right;
        Node<T> parent;

        // getters setters for Node
        Node<T> getLeft() {
            return left;
        }
    }
    Node<T> root;

    void insert(T value) {
        Node<T> n = new Node<T>(value);
        // further BST implementation
    }
}

// można również extendować Node-a
public class NewNode extends BST.Node<Integer> {
    // ...
}
```

Powyższy kod wykonuje się w trakcie kompilacji.

```c
CLI:
p: wybierz
> int
```

Prawie nienajgorzej:
```java
void CLI() {
    // decay / type erase method
    BST b;
    if ("int") 
        b = new BST<Integer>;
    else if("double")
        b = new BST<Double>;
    else if("string")
        b = new BST<String>;
    else
        throw new Exception("Unsupported type");

    // ale wtedy poniższe polecenie wywali się (ewentualnie, czyli na pewno) dopiero w runtime
    b.insert(5);
}
```

Wykorzystajmy technikę proxy. Obiekt wykorzystujący template, musi również być template-em.

```java
void CLI<T>() {
    BST<T> b;
    void run();
}
```

Handshake:
```java
String option;
System.in.read(option) // "int" // scanf in c++
if (op == "int") {
    CLI<Integer> c = new CLI();
    c.run();
}
else if(op =="double") {
    CLI<Double> c = new CLI();
    c.run();
}
```

Insert dla int:
```java
void insert(int val) {

}

CLI<T> {
    void run() {
        while (true) {
            get_command = cmd string
            get_value = cmd string
        }
    }
}

// masakracja
Integer f(string);
Double  f(string);

// ten sam typ -> ten sam kod
// ten sam kod -> różne typy 
// inny typ -> inny kod - dziedziczenie statyczne
```

Naprawmy ten problem:
```java
// specyfikacja typu
interface Parser<T>
    T.parse(string)
class ParseInt implements Parser<Integer> {
    Integer parse(String s) {
        return Integer.ParseToInteger(s)
    }
}
```

```c++
template <type T>
T add(T a, T b)  return a+b;

template <int>
int add(int a, int b) return a-b;
```

| Dziedziczenie dynamiczne      | Statyczne dziedziczenie | Statycnze dziedziczenie typu  |
| ------------------------------|-------------------------|-------------------------------|
| extends                       | \<T\>                   | \<Integer\>                   |
| ten sam typ funkcji, inny kod | inny typ ten sam kod    | inny typ inny kod             |

Dziwne aspkety javy:
```java
<?> //  
<*> // 
[REFLECTION] // zdobywanie metadanych od kompilatora w czasie runtime-u
```

Reflection pozwala na:
- zdobywanie informacji o klasach private
- zrobić coś co nie jest możliwe w czasie kompilacji
- zrobić cokolwiek w czasie runtime-u
