# List 3

- [List 3](#list-3)
- [Exercises](#exercises)
  - [Exercise 1](#exercise-1)
  - [Exercise 2](#exercise-2)
  - [Exercise 3](#exercise-3)
  - [Exercise 4 and Exercise 5](#exercise-4-and-exercise-5)
  - [Exercise 6](#exercise-6)

# Exercises

## Exercise 1

Task: (10pt) Napisz skrypt w Bashu, który pokazuje informacje o wszystkich procesach (podobne jak program ps aux). W zadaniu wykorzystaj system plików proc (standardowo w systemie Linux montowanym w katalogu /proc, man 5 proc) do pobrania informacji o procesach np. cat /proc/PID/status (i/lub /proc/PID/stat) wyświetla informacje o procesie PID. Wyświetl ppid, pid, comm, state, tty, rss, pgid, sid i poznaj dokładnie wszystkie wymienione oznaczenia! Dodatkowo wyświetl informację ile proces ma otwartych plików. Wszystkie te informacje o jednym procesie mają być "ładnie" (patrz np. man column) wyświetlone w jednym wierszu podobnie jak w programie ps. 

The script is available at [./ex1/ps.sh](./ex1/ps.sh).

I based my solution on proc_pid_stat(5) https://man7.org/linux/man-pages/man5/proc_pid_stat.5.html:
- (1) pid - process ID
- (2) comm - command name
- (3) state - state (R: running, S: sleeping, D: uninterruptible sleep, Z: zombie, T: traced or stopped)
- (4) ppid - parent process ID
- (5) pgrp - process group ID
- (6) session - session ID
- (7) tty_nr - controlling terminal
- (24) rss - resident set size

To list open files per process I used `lsof` like this:

```bash
lsof=$(ls /proc/$pid/fd 2> /dev/null | wc -l)
```

Redirecting stderr when there is no such directory or the user does not have necessary permission to access it.
In such case the result will be 0 as there are no output lines passed to the `wc` command.

## Exercise 2

Task: (15pt) Napisz skrypt w Bashu, który co sekundę prezentuje informacje o systemie operacyjnym. Dane pobierz wykorzystując pseudo system plików proc w Linuksie domyślnie zamontowanym w katalogu /proc (patrz man 5 proc) oraz sysfs (patrz man 5 sysfs). Skrypt powinien prezentować następujące informacje:

    Aktualną oraz średnią prędkość wysyłania i odbierania danych z sieci (odczytaj i zinterpretuj /proc/net/dev oraz wyświetl w B, KB lub MB w zależność od aktualnej prędkości) i
    Aktualne wykorzystanie rdzeni procesora dla każdego rdzenia osobno w procentach (patrz /proc/stat - man 5 proc) wraz z aktualną częstotliwością (patrz np. /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq dla cpu0) pracy rdzenia procesora (podobnie jak htop) i
    Jak długo system jest uruchomiony w dniach, godzinach, minutach i sekundach (/proc/uptime) i/lub
    Aktualny stan baterii w procentach (/sys/class/power_supply/BAT0/uevent) i
    Obciążenie systemu /proc/loadavg oraz
    Aktualne wykorzystanie pamięci /proc/meminfo (przeanalizuj co oznaczają 3 początkowe wiersze). 

W przypadku prędkości przesyłania danych skrypt powinien prezentować "graficznie" historię poprzednich pomiarów np. prosty wykres słupkowy. Przykładowe programy z wykresami na których można się wzorować to: s-tui lub bmon lub bpytop. Można wykorzystać inne znaki w UTF-8. Zobacz też informacje o komendzie tput np. link i/lub link. Układ oraz kolejność wyświetlanych informacji jest dowolna. 

The script is available at [./ex2/stat.sh](./ex2/stat.sh)

After careful lecture of both sysfs(5) and proc(5) I am able to show the following information:
1. Current and average network throughput (via /proc/net/dev)
   - Graph of the last 10 seconds of network throughput
2. CPU usage for each core (via /proc/stat) 
   - Current CPU core frequency (via /sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq)
3. Uptime (via /proc/uptime)
4. Battery status (via /sys/class/power_supply/BAT0/uevent) - if exists
5. System load (via /proc/loadavg)
6. Memory usage (via /proc/meminfo - first 3 rows)

Everything has been nicely described in the script itself, though the fact that I decided to print last 10 seconds of network throughput in a graphical way is worth mentioning here.
I simply printed a horizontal bar chart for both rx and tx throughput, keeping the same scale for both values. The scale has been normalized to the maximum value present in the 10s buffer.

## Exercise 3

Task: (10pt) Napisz skrypt w Bashu wykorzystujący REST API do pobierania danych z dwóch przykładowych źródeł np. Chuck Norris API i The Cat API lub dowolne inne które pobiera tekst i obrazki. Do zapytań RESTowych wykorzystaj curl lub wget do parsowania JSONa wystarczy program jq (pacman -S jq), dla osób korzystających z formatu XML dostępny jest program xmllint (pacman -S libxml2). Po uruchomieniu skryptu na ekranie pokaż obraz z bazy 'The Cat API' wykorzystując np. program img2txt (pacman -S libcaca) lub catimg oraz poniżej wyświetl losowy cytat z bazy Chucka Norrisa. 

The script is available at [./ex3/code.sh](./ex3/code.sh)

The script is self-explanatory.

## Exercise 4 and Exercise 5

Task 4: (10pt) Napisz program w języku C dla systemu Xv6, który pozwoli na wykonywanie prostych operacji arytmetycznych na liczbach całkowitych w konsoli nazwijmy go expr. Program dostając na wejście jako argumenty liczbę, operator i liczbę powinien wracać wynik tej operacji np. 

```bash
cpu0: starting 0
sb: size 1000 nblocks 941 ninodes 200 nlog 30 logstart 2 inodestart 32 bmap start 58
init: starting sh
$ expr 2 + 2
4
$ expr 10 / 3
3
$ expr 10 - 2
8
```

Task 5: (10pt)* Zmodyfikuj system operacyjny Xv6 (patrz m.in. na console.c) tak aby wyświetlać tekst w dowolnych kolorach. Możesz to zrobić podobnie wprowadzając prostą (wystarczy tylko do koloru) ANSI escape sequences lub wykorzystując np. '%' (który już jest), wtedy %1 - kolor niebieski, %2 - kolor czerwony itp. Napisz krótki program testowy hello wyświetlający 'Hello, World' we wszystkich kolorach dla Xv6. 

Due to the fact that I can run both exercises on the same `xv6` instance, I decided to merge them into one solution providing a [patchfile](./ex4-5/lab3.ex4.ex5.patch) to run the whole solution on the `xv6` system. I assume the initial system was cloned the lab path provided earlier (see list 1) was applied.

Solution to the 4-th task is available at [./ex4-5/expr.c](./ex4-5/expr.c) and to the 5-th task at [./ex4-5/console.c](./ex4-5/console.c) and [./ex4-5/hello.c](./ex4-5/hello.c) respectively.

I also edited the Makefile to compile and link these files properly, the changes are included in the patch file, but I also provide the Makefile for clarity at [./ex4-5/Makefile](./ex4-5/Makefile). 

## Exercise 6

This was a tough exercise, but I've managed to craete a working maze generator and player controls. The winning condition is to reach the end (max x, max y) of the maze. The player is starting
from the beginning (1, 1) of the maze. The maze is generated using the DFS algorithm.

The game is available at [./ex6/game.sh](./ex6/game.sh).

```bash
# ==The=Worst=Snake=Game=Ever=64==================================
# AUTHOR: Rafał Włodarczyk 2024-11-16
# DESCRIPTION: A simple maze game created in Bash. 
#              Find the exit.
# ===================================The=Worst=Snake=Game=Ever=64=

# ==Configuration=================================================
# -w, Optional: width of the maze (default: terminal width - 1)
# -h, Optional: height of the maze (default: terminal height - 1)
# ================================================================
```

