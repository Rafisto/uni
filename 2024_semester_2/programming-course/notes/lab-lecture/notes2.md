> na pierwszej i ostatniej stronie mają być sami uczniowie chrystusa

Obiektowość:

USOS Backend

- Kierunek ma 4 grupy studentów

```
class Kierunek
    Grupa[] grupy

class Grupa
    Student[] studenci

class Student
    int id
    string nazwisko
    float[] oceny

class Utils
    static srednia(oceny)
        return sum(oceny) / len(oceny)
```

Redundancja.

> J: czy można stworzyć klasę która zawiera metody statyczne i nie statyczne? xD

Rozwiązanie do kitu:

```ps
class Student
    int age;

Student s; 
s.age = 20;

Print(s.age)

// minus pół oceny
```

> Kukos Irritated: Od 5 minut o tym mówię

Rozwiązanie poprawne:

```ps
class Student
    private int age
    public Student(age)
        this.age = age 

    public getAge()
        // OBSERVABILITY
        return this.age       

s = new Student(18)
Print(s.getAge())
```

Gettery pod observability

Rozszerzamy klasę student

```ps
class Student
    private int age
    private int surname;
    private bool isActive;

    public Student(age, surname)
        if (age < 18)
            ERROR
        this.age = age
        this.surname = surname
        this.isActive = true

    public Student(surname)
        this.age = 18
        this.surname = surname
        this.isActive = true
```

Design by contract

```ps
int f(int n)
    if n < 18
        P("age should be greater than 18, got ${n}")

```

```
class Student
    private int age
    
    public Student (age)
        if age < 18
            throw new IllegalArgument("age should be greater than 18, got ${age}")
        this.age = age

try
    s = new Student(17)
catch IllegalArgument e
    P(e.message)
```

All built-in libraries are allowed. Valgrind... allowed.
