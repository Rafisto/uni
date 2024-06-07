Bare metal - Wątek
Wszystko inne - wiele wątków

Współbieżne - Kilka wątków, robiących inne rzeczy 

(HPC) Równoległe, Rozproszone:
- Map Reduce 


1 Core np. Pentium IV

```
-------------------->
```

Multicore np. Ryzen 5600

```
-------------------->
-------------------->
-------------------->
-------------------->
```

Przeplot

```c
int n = 3;
f() {
    if (++n >= 5) n=0;

    // NEVER CLAIM -> PROMELA (n będzie większy od 5)
    assert (n < 5);
}
```

```c
++n;
if (n >= 5) n=0;
assert(n < 5);
```

| Thread 1 | Thread 2   |
|----------|------------|
| `++n` (n=4) | --      |
| `if(n>=5)` False | -- |
| -- | `++n` (n=5)      |
| `assert(n<5)` | --    |
Boom

Use THREAD LOCKING:
```java
synchronized()
```

```java
f() {
    synchronize(this) {

    }
}
```

T1(C1)   | T2(C2)   |
Lock(C1) | ---      |
---      | Lock(C2) |
f        |          |

```java
bool isActive()
void activate()
void suspend()
```

```java
bool isActive = true;
return isActive();
return activate();
return suspend(); 
```

### 5 Chinese Philosopher Problem

```
o | o | o | o | o | (in a circle)
```

### Assumptions:
1. If a Thread changes color, nobody can read their color, until they finish changing it.

Parallel Serialization

| Thread 1    | Thread 2    |
| t1.ch       | t2.ch       |
| t1.ret2.get | t1.ref1.get |

See Linux: Scheduler:
- spinlock: `while(lock) { ... }`
- mutex - `while(lock) { sleep(1); }`
- semaphore - `while(numLock < n) { sleep(1); }`

```java
for(...) {
    for(...) {
        arr[i][j] = new T(locker);
    }
}
```

STARVATION - LIGHT LOCK

```java
void changeColor() {
    synchronized(this.locker) {
        color = !color;
    }
}
```

2. When I change color I do not sleep
3. When sb reads my color I do not sleep
4. When sb reads my state I do not change my state. 
5. If my neighbor is changes their color, I do not change my state.

```java
synchronized changeColor() { sync(locker) { sync(neighbor1) { sync(neighbor2) { ... } } } }
synchronized changeState() { }
synchronized getColor() { }
synchronized getState() { }
synchronized getMyReference() { }
```