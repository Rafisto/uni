## XV6 -  Struktura systemu plików

Cała logika znajduje się w `fs.c`

```plaintext
+ boot + super + log | + inodes | | + bit map | + data | ... | data +
+ 0    + 1     + 2,3   + 4,5,6      + 7,8       + 9...  
```

512 bajtów = 200 w hex co sektor

- Blok 0
  - blok rozruchowy
- Blok 1
  - metadane dotyczące systemu plików - zgodne ze struct `superblock`
  - rozmiar obrazu systemu
  - liczba bloków (1000) 
  - liczba inode-ów (pliki bez nazw, nazwy plików są w innych inode-ach)
  - ...

Bitmapa - jak alokować pamięć w systemie plików, bitmapa wskazuje na to które bloki są zajęte, a które wolne.
$1000/8=125$ bajtów potrzebnych na bitmapę.

`*` w hexdump oznacza powtarzalny segment (z reguły oznacza to same zera)

Buffer cache umożliwia zrównoleglenie operacji na dysku.
- Synchronizacja - w jądrze istnieje tylko jedna kopa bloku danych
- Buforowanie - wydajny odczyt i zapis

> Zapisuje pliki i nagle odcina prąd. Wyłączyłem journalling, mogę instalujemy system od nowa.

### INode

W systemie plików mamy ograniczoną liczbę INode-ów. Są to pliki bez nazwy, które przechowują dane.

Zobacz `inode` (in memory copy of inode) oraz `dinode` (disk-inode).

Inode ma np. 12 adresów oraz pointer (indirect) do kolejnego bloku adresowego (128 kolejnych adresów)
Maksymalna długość pliku 12 * 512 + 128 * 512 = 71680 bajtów

Inode (hex_inode * 0x200) pozwala wyliczyć fizyczny adres - blok w którym znajdują się dane.

W solidnych systemach plików występuje triple indirect (kilka gb).

### Directory INode - Dirnode

struct `dirent` - inum, name. <- który inode oraz jaka jest jego nazwa

### Wear leveling

Komputer wewnątrz dysku SSD utrzymuje taki sam poziom zapisu na wszystkich komórkach, dzięki temu możemy wykonać więcej zapisów niż wynikałoby to z żywotności poszczególnej komórki (`< 10 000`).

W kartach SD nie ma wear leveling, ale systemy FAT zostały zaprojektowane żeby w pierwszej kolejności pisać do następnego wolnego sektora, nawet jeśli pojawiają się dziury.

## File

W UNIX-ie, w momencie gdy mamy otwarty fd, i usuniemy go to plik ciągle będzie widoczny, jako deleted.

```
# fopen('hello')
# sleep(1000)
# rm hello
cat /proc/<pid>/fd/3 -> hello contents
# fclose('hello')
```

## Język C

Normalnie nie ukrytego kopiowania (array), ale w przypadku `struct` już jest.

```asm
rep movsl ...
```

Alignment do wielokrotności największego typu, w większości wypadków do 4 bajtów.
- `malloc()` zawsze wraca wskaźniki, które są wielokrotnością 8. Na stacku również.

The alignment rules are weird:

```c
typedef struct {
    char b;
    int i;
} S1;

sizeof(S1) = 8; // (char aligns to 4 bytes)
```

```c
typedef struct {
    char b;
    long l;
} S2;

sizeof(S2) = 16; // (char aligns to 8 bytes) 

// however

```c
typedef struct {
    char b;
    int  i;
    long l;
} S3;

sizeof(S3) = 16; // (char aligns to 4 bytes)
``` 

## Egzamin

6 pytań SO:

Zakres z podsumowania. Przewertować wykłady. 

- Może się zdarzyć GDT wyjaśnij.
- Zobacz Podsumowanie: CF carrry, SF sign, OF overflow (signed/unsigned interpretation), Z zero
- Przerwania - sprzętowe programowe 
- Realizacja stosu: pushe, skoki (trap) 
- Zaalokować zrobić 2 elementową tablicę pagingu.

6 pytań AK:
