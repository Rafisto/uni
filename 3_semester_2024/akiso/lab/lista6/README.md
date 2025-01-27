# List 6

- [List 6](#list-6)
- [Patch](#patch)
- [Exercises](#exercises)
  - [Exercise 1](#exercise-1)
  - [Exercise 2](#exercise-2)
  - [Exercise 3](#exercise-3)
  - [Exercise 4](#exercise-4)

# Patch

Załączam [pełny patch](./all.patch) do upstream xv6 (https://github.com/mit-pdos/xv6-public) z rozwiązaniem zadania z listy 6, oraz [diff ze zmianami tylko do tej listy](./lista6.patch), w którym wyraźnie widać jakie całościowe zmiany są potrzebne do wprowadzenia rozwiązań czterech poniższych zadań.

# Exercises

## Exercise 1

(10pt) Zaimplementuj w XV6 funkcje vmprint, która drukuje zawartość tabeli stronnicowania procesu (pgdir).

Przedstawiam `vmprint` dołączony do kodu `vm.c`:

```c
// vm.c
// [...]

// 6.1 add vmprint defintion
void vmprint(pde_t *pgdir) {
  cprintf("pgdir %p\n", pgdir);

  for (int i = 0; i < 512; i++) 
    if (pgdir[i] & PTE_P) { 
      uint pa = PTE_ADDR(pgdir[i]);
      cprintf(".. %d: pde %p pa %p\n", i, pgdir[i], pa);

      pte_t* pt = (pte_t*)P2V(pa); 
      for (int j = 0; j < 1024; j++) {
          if (pt[j] & PTE_P) {
              uint pte_pa = PTE_ADDR(pt[j]);
              cprintf(".. .. %d: pte %p pa %p\n", j, pt[j], pte_pa);
          }
      }
  }
}
```

Oraz program testowy sprawdzający działanie `vmprint`:

```c
// 6.1 add testvm.c
#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    // allocate 5 pages of memory using sbrk
    void *mem = sbrk(5 * 4096);

    // write to the first byte of each page
    for (int i = 0; i < 5; i++)
    {
        *(char *)(mem + i * 4096) = 'a' + i;
    }

    // exit
    exit();
}
```

Przedstawiam wynik działania programu `testvm` w skompilowanym systemie. Jak widać doszło do sukcesywnego alokowania 5 stron pamięci:

```bash
$ testvm
exec - pgdir 8df23000
.. 0: pde dee1007 pa dee1000
.. .. 0: pte dee2007 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf007 pa dedf000
exit - pgdir 8df23000
.. 0: pde dee1027 pa dee1000
.. .. 0: pte dee2027 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf067 pa dedf000
.. .. 3: pte dfbc067 pa dfbc000
.. .. 4: pte df76067 pa df76000
.. .. 5: pte dfbf067 pa dfbf000
.. .. 6: pte dfc0067 pa dfc0000
.. .. 7: pte dfc1067 pa dfc1000
```

## Exercise 2

(20pt) Napisz w XV6 wywołanie systemowe, które wyświetlania informacje o pamięci. Zaimplementuj:

- usedvp() powinno zwrócić liczbę stron wirtualnych/logicznych w części użytkownika przestrzeni adresowej procesu, do rozmiaru programu zapisanego w struct proc. Musisz również uwzględnić stronę ochrony stosu w swoich obliczeniach.
- usedpp() powinno zwrócić liczbę stron fizycznych w części użytkownika przestrzeni adresowej procesu. Musisz policzyć tę liczbę, przechodząc przez tabelę stron procesu i licząc liczbę wpisów w tabeli stron, które mają przypisany prawidłowy adres fizyczny. 

Przedstawiam implementację wywołania systemowego `sys_usedvp` oraz `sys_usedpp`. Pierwszy z nich zwraca liczbę stron wirtualnych bezpośrednio z parametrów struct proc dla bieżącego procesu, natomiast drugi w ramach iteracji po stronach wirtualnych zwraca liczbę stron fizycznych, które są zmapowane w przestrzeni adresowej procesu:

```c
// sysfile.c
// [...]

// 6.2 add a syscall usedvp
int sys_usedvp(void)
{
  struct proc *curproc = myproc();
  uint sz = curproc->sz;
  uint num_pages = sz / PGSIZE;

  return num_pages;
}

// 6.2 add a syscall usedpp
int sys_usedpp(void)
{
  struct proc *curproc = myproc();
  pde_t *pgdir = curproc->pgdir;
  pte_t *pgtab;
  uint num_pages = 0;
  uint va = 0;

  for (va = 0; va < curproc->sz; va+= PGSIZE) {
    pgtab = walkpgdir(pgdir, (void *)va, 0);
    // exists and mapped
    if (pgtab && (*pgtab & PTE_P)) {
      num_pages++;
    }
  }

  return num_pages;
}
```

Program testowy obejmuje wywołanie `sbrk`, które początkowo alokuje 1, następnie 2, a końcowo dealokuje 3 strony pamięci.

```c
// 6.2 add testvinfo.c
#include "types.h"
#include "user.h"

void print_usage(const char *message) {
  int used_virtual = usedvp();
  int used_physical = usedpp();
  
  printf(1, "%s\n", message);
  printf(1, "(usedvp) Number of used virtual pages: %d\n", used_virtual);
  printf(1, "(usedpp) Number of used physical pages: %d\n", used_physical);
}

int main() {
  print_usage("Initial usage:");

  // Allocate a page
  sbrk(4096);
  print_usage("After allocating a page:");

  // Allocate two pages
  sbrk(4096 * 2);
  print_usage("After allocating two pages:");

  // Deallocate three pages
  sbrk(-4096 * 3);
  print_usage("After deallocating three pages:");

  exit();
}
```

Wynikiem programu jest poprawne zliczenie stron wirtualnych oraz fizycznych w zależności od alokacji i dealokacji pamięci:

```bash
$ testvinfo
exec - pgdir 8df23000
.. 0: pde dee1007 pa dee1000
.. .. 0: pte dee2007 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf007 pa dedf000
Initial usage:
(usedvp) Number of used virtual pages: 3
(usedpp) Number of used physical pages: 3
After allocating a page:
(usedvp) Number of used virtual pages: 4
(usedpp) Number of used physical pages: 4
After allocating two pages:
(usedvp) Number of used virtual pages: 6
(usedpp) Number of used physical pages: 6
After deallocating three pages:
(usedvp) Number of used virtual pages: 3
(usedpp) Number of used physical pages: 3
exit - pgdir 8df23000
.. 0: pde dee1027 pa dee1000
.. .. 0: pte dee2027 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf067 pa dedf000
```

## Exercise 3

(10pt)* Napisz w XV6 prostą wersja mapowania pamięci za pomocą wywołania systemowego `mmap`, które alokuje fizyczną pamięć on-demand.

```c
// 6.3 add a syscall mmap
int sys_mmap(void) 
{
  int size;

  // must be an integer
  if(argint(0, (int*)&size) < 0){
    return -1;
  }

  // must be a multiple of a page
  if (size > 0 && size % PGSIZE != 0) {
    return -1;
  }

  // grow virtual memory size
  struct proc *curproc = myproc();
  curproc->sz += size;
  
  switchuvm(curproc);

  return curproc->sz - size;
}
```

Program testowy zostanie ukazany w zadaniu 4, ponieważ tam `mmap` posiada pełną implementacje.

## Exercise 4

(20pt)* W tym zadaniu dalej rozszerzamy zadanie poprzednie na pełne działanie mmap. Na początku musimy przydzielać pamięć fizyczną w ramach obsługi błędu strony. Ponadto, jeśli mapujesz w pamięci więcej niż jedną stronę, pamięć fizyczna powinna być przydzielana tylko dla tych stron, do których uzyskuje się dostęp, a nie dla wszystkich stron w regionie mapowanym w pamięci. Ponownie użyj liczby stron wirtualnych/fizycznych, aby sprawdzić, czy strony fizyczne są przydzielane tylko na żądanie. Udostępniliśmy prosty program testowy do przetestowania implementacji.

Dodałem case do `trap.c` wykrywający czy adres, który wywołał **T_PGFLT** znajduje się w wirtualnej przestrzeni adresowej programu czy nie. Jeśli nie, to następuje tradycyjny page fault. Jeżeli tak, to znaczy że musimy dynamicznie zaprovisionować pamięć dla tego adresu. W tym celu zbieramy adres z rejestru **CR2**, normalizujemy do wielokrotności strony, a następnie zestawiamy pamięć fizyczną dla strony wirtualnej. W przypadku sukcesu, zmieniamy rozmiar programu, zmieniamy przestrzeń adresową procesu i wypisujemy informacje o sukcesie. W przypadku niepowodzenia, zabijamy proces. 

```c
case T_PGFLT:
// Assume dynamic mmap failed.
uint va = rcr2();

if (va <= myproc()->sz) {
    cprintf("pid %d %s: dynamic mmap available at %x.\n", myproc()->pid, myproc()->name, va);

    // impl alloc
    uint vapg = PGROUNDDOWN(va);

    if (allocuvm(myproc()->pgdir, vapg, vapg + PGSIZE) == 0) {
        cprintf("pid %d %s: page fault at %x.\n", myproc()->pid, myproc()->name, va);
        myproc()->killed = 1;
    }
    else {
        cprintf("pid %d %s: resized page at %x.\n", myproc()->pid, myproc()->name, va);
        switchuvm(myproc());
        cprintf("pid %d %s: switched to new page at %x.\n", myproc()->pid, myproc()->name, va);
        break;
    }
}
else {
    cprintf("pid %d %s: page fault at %x.\n",
            myproc()->pid, myproc()->name, va);
    myproc()->killed = 1;
}
break;
```

Program testowy obejmuje wykonanie czynności sprawdzających dynamiczne provisionowanie stron pamięci. W tym celu dokonuje kilku `mmap`-ów oraz próbuję dostać się do pamięci, która istnieje (żeby pokazać że standardowy przypadek użycia nie uległ zmianie) oraz do pamięci, która istnieje tylko wirtualnie (żeby pokazać że dynamiczne provisionowanie działa).

Cudowną zaletą napisanego handlera w `trap.c` jest to, że alokuje jedynie wykorzystywane strony, dzięki czemu w rozkładzie `vmprint` widać, że strony fizyczne są faktycznie przydzielane tylko na żądanie, a strony pomiędzy nie są alokowane.

Pełne wykonanie programu testmmap:

```bash
$ testmmap
exec - pgdir 8df23000
.. 0: pde dee1007 pa dee1000
.. .. 0: pte dee2007 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf007 pa dedf000
Initial usage:
(usedvp) Number of used virtual pages: 3
(usedpp) Number of used physical pages: 3
mmap succeeded with address 3000
After allocating a page:
(usedvp) Number of used virtual pages: 4
(usedpp) Number of used physical pages: 3
mmap succeeded with address 4000
After allocating two pages:
(usedvp) Number of used virtual pages: 6
(usedpp) Number of used physical pages: 3
Trying to access valid physical memory at address 2000
Value at valid address: 
Trying to access non-existent physical memory at address 5000
pid 3 testmmap: dynamic mmap available at 5000.
pid 3 testmmap: resized page at 5000.
pid 3 testmmap: switched to new page at 5000.
Value at on-demand created address: 
Trying to write 'a' to freshly allocated memory
Value at freshly allocated address: a
After accessing non-existent physical memory:
(usedvp) Number of used virtual pages: 6
(usedpp) Number of used physical pages: 4
exit - pgdir 8df23000
.. 0: pde dee1027 pa dee1000
.. .. 0: pte dee2027 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf067 pa dedf000
.. .. 5: pte dfbc067 pa dfbc000
```

Kluczowy element poniższych logów to koniec:

```bash
(usedvp) Number of used virtual pages: 6
(usedpp) Number of used physical pages: 3

# ... try access 6th virtual page

(usedvp) Number of used virtual pages: 6
(usedpp) Number of used physical pages: 4
exit - pgdir 8df23000
.. 0: pde dee1027 pa dee1000
.. .. 0: pte dee2027 pa dee2000
.. .. 1: pte dee0003 pa dee0000
.. .. 2: pte dedf067 pa dedf000
.. .. 5: pte dfbc067 pa dfbc000
```

W pełnych logach widać również, że zarówno czytanie, jak i pisanie do tego zakresu pamięci jest możliwe.