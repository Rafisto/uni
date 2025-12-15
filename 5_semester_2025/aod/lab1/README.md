## Algorytmy Optymalizacji Dyskretnej - Lista 1

Rafał Włodarczyk 279762

- [Algorytmy Optymalizacji Dyskretnej - Lista 1](#algorytmy-optymalizacji-dyskretnej---lista-1)
- [Zadanie 1](#zadanie-1)
  - [Testy](#testy)
    - [DFS](#dfs)
    - [`test-01-directed`](#test-01-directed)
    - [`test-01-undirected`](#test-01-undirected)
    - [`test-02-directed`](#test-02-directed)
    - [`test-02-undirected`](#test-02-undirected)
    - [`test-03-directed`](#test-03-directed)
    - [`test-03-undirected`](#test-03-undirected)
    - [BFS](#bfs)
    - [`test-01-directed`](#test-01-directed-1)
    - [`test-01-undirected`](#test-01-undirected-1)
    - [`test-02-directed`](#test-02-directed-1)
    - [`test-02-undirected`](#test-02-undirected-1)
    - [`test-03-directed`](#test-03-directed-1)
    - [`test-03-undirected`](#test-03-undirected-1)
- [Zadanie 2](#zadanie-2)
  - [Testy](#testy-1)
- [Zadanie 3](#zadanie-3)
  - [Testy](#testy-2)
- [Zadanie 4](#zadanie-4)
  - [Testy](#testy-3)

## Zadanie 1

### Testy

#### DFS

#### `test-01-directed`

```
find tests/* -exec ./a.out dfs {} --tree \;
File: tests/test-01-directed:
DFS Tree:
1
|- 3
|- 6
|- 5
|- 2
|- 4
Traversal: 1 3 6 5 2 4 
Time: 9472 ns (0 ms, 0 s)
```

#### `test-01-undirected`

```
File: tests/test-01-undirected:
DFS Tree:
1
|- 3
|- 6
   |- 5
      |- 4
         |- 2
Traversal: 1 3 6 5 4 2 
Time: 10266 ns (0 ms, 0 s)
```

#### `test-02-directed`

```
File: tests/test-02-directed:
DFS Tree:
1
|- 4
|- 8
   |- 7
      |- 3
|- 2
|- 6
   |- 5
Traversal: 1 4 8 7 3 2 6 5 
Time: 12189 ns (0 ms, 0 s)
```

#### `test-02-undirected`

```
File: tests/test-02-undirected:
DFS Tree:
1
|- 5
|- 6
   |- 7
      |- 8
         |- 4
            |- 3
               |- 2
Traversal: 1 5 6 7 8 4 3 2 
Time: 19808 ns (0 ms, 0 s)
```

#### `test-03-directed`


```
File: tests/test-03-directed:
DFS Tree:
1
|- 5
|- 6
   |- 9
      |- 8
      |- 7
         |- 4
|- 3
|- 2
Traversal: 1 5 6 9 8 7 4 3 2 
Time: 22582 ns (0 ms, 0 s)
```

#### `test-03-undirected`

```
File: tests/test-03-undirected:
DFS Tree:
1
|- 5
|- 7
   |- 9
      |- 8
         |- 4
            |- 2
      |- 6
         |- 3
Traversal: 1 5 7 9 8 4 2 6 3 
Time: 16769 ns (0 ms, 0 s)
```

#### BFS


#### `test-01-directed`

```
find tests/* -exec ./a.out bfs {} --tree \;
File: tests/test-01-directed:
1
|- 2
|- 3
   |- 4
   |- 5
   |- 6
Traversal: 1 2 3 4 5 6 
Time: 16243 ns (0 ms, 0 s)
```

#### `test-01-undirected`

```
File: tests/test-01-undirected:
1
|- 2
|- 3
   |- 4
   |- 5
   |- 6
Traversal: 1 2 3 4 5 6 
Time: 13705 ns (0 ms, 0 s)
```

#### `test-02-directed`

```
File: tests/test-02-directed:
1
|- 2
|- 4
   |- 3
   |- 6
   |- 8
      |- 5
      |- 7
Traversal: 1 2 4 3 6 8 5 7 
Time: 10648 ns (0 ms, 0 s)
```

#### `test-02-undirected`

```
File: tests/test-02-undirected:
1
|- 2
|- 4
|- 5
   |- 3
   |- 6
   |- 8
      |- 7
Traversal: 1 2 4 5 3 6 8 7 
Time: 18179 ns (0 ms, 0 s)
```

#### `test-03-directed`

```
File: tests/test-03-directed:
1
|- 2
|- 3
|- 5
   |- 4
   |- 6
      |- 8
      |- 7
      |- 9
Traversal: 1 2 3 5 4 6 8 7 9 
Time: 13837 ns (0 ms, 0 s)
```

#### `test-03-undirected`

```
File: tests/test-03-undirected:
1
|- 2
|- 3
|- 5
   |- 4
   |- 6
   |- 7
      |- 8
      |- 9
Traversal: 1 2 3 5 4 6 7 8 9 
Time: 21834 ns (0 ms, 0 s)
```

## Zadanie 2

### Testy

```
find tests/* -exec ./a.out {} \;
File: tests/g2a-1.txt: graph is acyclic.
1 5 9 13 2 6 10 14 3 7 11 15 4 8 12 16 
Time: 19846 ns (0 ms, 0 s)
File: tests/g2a-2.txt: graph is acyclic.
1 11 21 31 41 51 61 71 81 91 2 12 22 32 42 52 62 72 82 92 3 13 23 33 43 53 63 73 83 93 4 14 24 34 44 54 64 74 84 94 5 15 25 35 45 55 65 75 85 95 6 16 26 36 46 56 66 76 86 96 7 17 27 37 47 57 67 77 87 97 8 18 28 38 48 58 68 78 88 98 9 19 29 39 49 59 69 79 89 99 10 20 30 40 50 60 70 80 90 100 
Time: 34340 ns (0 ms, 0 s)
File: tests/g2a-3.txt: graph is acyclic.
Time: 377145 ns (0 ms, 0 s)
File: tests/g2a-4.txt: graph is acyclic.
Time: 8789165 ns (8 ms, 0 s)
File: tests/g2a-5.txt: graph is acyclic.
Time: 253749485 ns (253 ms, 0 s)
File: tests/g2a-6.txt: graph is acyclic.
Time: 3531539190 ns (3531 ms, 3 s)
File: tests/g2b-1.txt: path: 1 2 3 7 11 6 and now 7.
cycle has been found
Time: 42306 ns (0 ms, 0 s)
File: tests/g2b-2.txt: path: 1 2 3 4 5 6 16 26 36 46 56 45 and now 46.
cycle has been found
Time: 55209 ns (0 ms, 0 s)
File: tests/g2b-3.txt: cycle has been found
Time: 264888 ns (0 ms, 0 s)
File: tests/g2b-4.txt: cycle has been found
Time: 4672124 ns (4 ms, 0 s)
File: tests/g2b-5.txt: cycle has been found
Time: 189764945 ns (189 ms, 0 s)
File: tests/g2b-6.txt: cycle has been found
Time: 2448814193 ns (2448 ms, 2 s)
```

## Zadanie 3

### Testy

```
find tests/* -exec  ./a.out {} \;
File: tests/g3-1.txt:
SCC Count: 5
- SCC of size 5
{ 1 5 4 3 2 }
- SCC of size 4
{ 12 15 14 13 }
- SCC of size 4
{ 6 8 9 7 }
- SCC of size 2
{ 10 11 }
- SCC of size 1
{ 16 }
Time: 22941 ns (0 ms, 0 s)
File: tests/g3-2.txt:
SCC Count: 5
- SCC of size 6
{ 1 6 5 4 3 2 }
- SCC of size 40
{ 67 106 105 104 103 102 101 100 99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80 79 78 77 76 75 74 73 72 71 70 69 68 }
- SCC of size 36
{ 7 13 19 25 31 37 38 39 40 41 42 36 35 29 28 34 22 21 27 33 15 14 20 26 32 8 9 16 10 23 17 11 30 24 18 12 }
- SCC of size 24
{ 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 }
- SCC of size 1
{ 107 }
Time: 37687 ns (0 ms, 0 s)
File: tests/g3-3.txt:
SCC Count: 5
- SCC of size 7
- SCC of size 400
- SCC of size 400
- SCC of size 200
- SCC of size 1
Time: 142678 ns (0 ms, 0 s)
File: tests/g3-4.txt:
SCC Count: 5
- SCC of size 8
- SCC of size 4000
- SCC of size 3600
- SCC of size 2400
- SCC of size 1
Time: 1697869 ns (1 ms, 0 s)
File: tests/g3-5.txt:
SCC Count: 5
- SCC of size 9
- SCC of size 40000
- SCC of size 40000
- SCC of size 20000
- SCC of size 1
Time: 14215003 ns (14 ms, 0 s)
File: tests/g3-6.txt:
SCC Count: 5
- SCC of size 10
- SCC of size 400000
- SCC of size 360000
- SCC of size 240000
- SCC of size 1
Time: 123749000 ns (123 ms, 0 s)
```

## Zadanie 4

### Testy

```
find tests/* -exec  ./a.out {} \;
File: tests/d4a-1.txt:Graph is bipartite
Red: { 1 3 6 8 9 11 14 16 }
Black: { 2 4 5 7 10 12 13 15 }
Time: 12964 ns (0 ms, 0 s)
File: tests/d4a-2.txt:Graph is bipartite
Red: { 1 3 5 7 9 12 14 16 18 20 21 23 25 27 29 32 34 36 38 40 41 43 45 47 49 52 54 56 58 60 61 63 65 67 69 72 74 76 78 80 81 83 85 87 89 92 94 96 98 100 }
Black: { 2 4 6 8 10 11 13 15 17 19 22 24 26 28 30 31 33 35 37 39 42 44 46 48 50 51 53 55 57 59 62 64 66 68 70 71 73 75 77 79 82 84 86 88 90 91 93 95 97 99 }
Time: 29171 ns (0 ms, 0 s)
File: tests/d4a-3.txt:Graph is bipartite
Time: 49623 ns (0 ms, 0 s)
File: tests/d4a-4.txt:Graph is bipartite
Time: 297850 ns (0 ms, 0 s)
File: tests/d4a-5.txt:Graph is bipartite
Time: 5873373 ns (5 ms, 0 s)
File: tests/d4a-6.txt:Graph is bipartite
Time: 38808766 ns (38 ms, 0 s)
File: tests/d4b-1.txt:Graph is not bipartite
Time: 8912 ns (0 ms, 0 s)
File: tests/d4b-2.txt:Graph is not bipartite
Time: 10651 ns (0 ms, 0 s)
File: tests/d4b-3.txt:Graph is not bipartite
Time: 28366 ns (0 ms, 0 s)
File: tests/d4b-4.txt:Graph is not bipartite
Time: 158283 ns (0 ms, 0 s)
File: tests/d4b-5.txt:Graph is not bipartite
Time: 2696816 ns (2 ms, 0 s)
File: tests/d4b-6.txt:Graph is not bipartite
Time: 18175182 ns (18 ms, 0 s)
File: tests/u4a-1.txt:Graph is bipartite
Red: { 1 4 5 6 7 }
Black: { 2 3 8 9 10 11 12 13 14 15 }
Time: 9336 ns (0 ms, 0 s)
File: tests/u4a-2.txt:Graph is bipartite
Red: { 1 4 5 6 7 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 }
Black: { 2 3 8 9 10 11 12 13 14 15 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 }
Time: 18356 ns (0 ms, 0 s)
File: tests/u4a-3.txt:Graph is bipartite
Time: 29794 ns (0 ms, 0 s)
File: tests/u4a-4.txt:Graph is bipartite
Time: 372927 ns (0 ms, 0 s)
File: tests/u4a-5.txt:Graph is bipartite
Time: 3047253 ns (3 ms, 0 s)
File: tests/u4a-6.txt:Graph is bipartite
Time: 24648394 ns (24 ms, 0 s)
File: tests/u4b-1.txt:Graph is not bipartite
Time: 10117 ns (0 ms, 0 s)
File: tests/u4b-2.txt:Graph is not bipartite
Time: 11094 ns (0 ms, 0 s)
File: tests/u4b-3.txt:Graph is not bipartite
Time: 16918 ns (0 ms, 0 s)
File: tests/u4b-4.txt:Graph is not bipartite
Time: 212215 ns (0 ms, 0 s)
File: tests/u4b-5.txt:Graph is not bipartite
Time: 1183890 ns (1 ms, 0 s)
File: tests/u4b-6.txt:Graph is not bipartite
Time: 9538166 ns (9 ms, 0 s)
```
