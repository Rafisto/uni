## Dane

Rafał Włodarczyk 279762

## Tests setup

Unpack and run make

```bash
tar -xzf ch9-1.1.tar.gz
cd ch9-1.1
make
make gen
```

And see that `./inputs` is now populated with (see `docs/families` for explanations):
- Random4-C
- Random4-n
- Square-C
- Square-n
- USA-road-d
- USA-road-t

Todo list:
- [ ] Zaimplementuj Dijkstre z Binary Heap
- [ ] Zaimplementuj Diala z C + 1
- [ ] Zaimplementuj Radix Heap
- [ ] Dodaj wywołaania
  - [ ] `-d -ss -oss`
  - [ ] `-d -p2p -op2p`
- [x] Makefiles
- [ ] Przeprowadź testy z wykresami - mierz czas (1) od min wierzchołka i (2) średnią z losowo wybranych 5 wierzchołków
  - [ ] ss Random4-n, Random 4-C
  - [ ] ss Long-n, Square-n
  - [ ] ss Long-C, Square-C
  - [ ] ss USA-road-t
- [ ] Przeprowadź testy z tabelką - mierz czas od (1) min index do max index i (2) średnią z losowo wybranych 4 par wierzchołków
  - [ ] p2p największe z Random4-n, Random 4-C 
  - [ ] p2p największe z Long-n, Square-n
  - [ ] p2p największe z Long-C, Square-C
  - [ ] p2p największe z USA-road-t
