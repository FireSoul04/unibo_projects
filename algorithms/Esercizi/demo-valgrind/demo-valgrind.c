/****************************************************************************
 *
 * demo-valgrind.c -- dimostrazione uso di valgrind
 *
 * Copyright (C) 2022--2024 Moreno Marzolla
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 ****************************************************************************/

/***
% LabASD - Dimostrazione uso di valgrind
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2024-02-24

Questo programma mostra l'uso del comando
[valgrind](https://valgrind.org/) disponibile in ambiente
Linux. `valgrind` consente di individuare, tra le altre cose, _memory
leak_ (aree di memoria dinamica che non vengono mai liberate), accessi
al di fuori dei limiti degli array (accessi _out-of-bound_) e uso di
variabili non inizializzate. Non è uno strumento infallibile: in
alcuni casi non rileva errori anche se presenti, quindi va usato con
consapevolezza. Purtroppo `valgrind` [non è disponibile su
Windows](https://valgrind.org/info/platforms.html). Come alternativa
si può provare [Dr. Memory](https://drmemory.org/) (disponibile per
Windows, Linux e MacOSX), con il quale però non ho esperienza.

Questo programma compila normalmente. Visual Studio potrebbe segnalare
un _warning_ in corrispondenza della `malloc()` se non si controlla
esplicitamente che il valore da essa restituito sia diverso da `NULL`
(questo è uno dei tanti esempi di warning inutili segnalati da VS);
per evitare ciò si fa il controllo usando la macro `assert()`. Il
programma è però **errato** perché sono presenti costrutti il cui
comportamento è indefinito. Con "comportamento indefinito" si intende
che su certi sistemi potrebbe terminare, mentre su altri potrebbe
produrre errori o crash in fase di esecuzione.

È importante ribadire che questo programma **deve essere, e sarà
considerato errato anche nel caso in cui sembri terminare
correttamente**.

Per compilare:

        gcc -std=c90 -Wall -Wpedantic -g demo-valgrind.c -o demo-valgrind

(il flag `-g` serve per includere delle informazioni di debug nel
programma eseguibile, in modo che `valgrind` mostri anche i numeri di
linea in cui si verificano eventuali problemi).

Per eseguire:

        valgrind ./demo-valgrind

L'output dipende dalla versione di `valgrind` e del compilatore;
comunque, sul mio sistema compare qualcosa del genere:

```
==19137== Memcheck, a memory error detector
==19137== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==19137== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==19137== Command: ./demo-valgrind
==19137== 
==19137== Invalid write of size 4
==19137==    at 0x10920B: main (demo-valgrind.c:259)
==19137==  Address 0x4a6c068 is 0 bytes after a block of size 40 alloc'd
==19137==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==19137==    by 0x1091CC: main (demo-valgrind.c:249)
```

Indica che è stato effettuato un accesso out-of-bound in scrittura,
cioè si è tentato di modificare un elemento al di fuori dei limiti
dell'array `a[]`; `valgrind` segnala la linea dove è avvenuto
l'accesso in scrittura (riga 259) e la riga in cui l'array è stato
allocato con la `malloc()` (riga 249).

```
==19137== 
==19137== Invalid read of size 4
==19137==    at 0x109225: main (demo-valgrind.c:262)
==19137==  Address 0x4a6c068 is 0 bytes after a block of size 40 alloc'd
==19137==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==19137==    by 0x1091CC: main (demo-valgrind.c:249)
```

Indica che è stato effettuato un accesso out-of-bound in
lettura. Anche qui viene riportata la riga dell'accesso in lettura
(riga 262) e la riga in cui l'array è stato allocato (riga 249).

```
==19137== 
10
```

Output del programma.

```
==19137== Conditional jump or move depends on uninitialised value(s)
==19137==    at 0x109242: main (demo-valgrind.c:264)
```

Indica che il comportamento del programma dipende da un valore
indefinito. Si fa riferimento al test dell'if alla riga 264.

```
==19137==
Falso
```

Output del programma.

```
==19137== 
==19137== HEAP SUMMARY:
==19137==     in use at exit: 40 bytes in 1 blocks
==19137==   total heap usage: 2 allocs, 1 frees, 1,064 bytes allocated
```

"in use at exit: 40 bytes" indica che al termine dell'esecuzione sono
rimasti 40 byte di memoria allocata ma non liberata. Effettivamente
questa memoria corrisponde all'array `a` di dimensione 10: su questa
architettura un intero occupa 4 byte da cui $4 \times 10 = 40B$.

```
==19137== 
==19137== LEAK SUMMARY:
==19137==    definitely lost: 40 bytes in 1 blocks
==19137==    indirectly lost: 0 bytes in 0 blocks
==19137==      possibly lost: 0 bytes in 0 blocks
==19137==    still reachable: 0 bytes in 0 blocks
==19137==         suppressed: 0 bytes in 0 blocks
==19137== Rerun with --leak-check=full to see details of leaked memory
==19137== 
==19137== Use --track-origins=yes to see where uninitialised values come from
==19137== For lists of detected and suppressed errors, rerun with: -s
==19137== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
```

## Soluzione alternativa che non richiede valgrind

Versioni recenti del compilatore gcc sono in grado di inserire dei
controlli nell'eseguibile che proteggono da alcuni problemi legati
agli accessi alla memoria. Per abilitare i controlli occorre compilare
con i parametri `-fsanitize=address -g` sulla riga di comando, come
segue:

        gcc -std=c90 -Wall -Wpedantic -g -fsanitize=address demo-valgrind.c -o demo-valgrind

> L'opzione `-fsanitize=address` non è disponibile per tutti i sistemi
> operativi, e anche dove presente non effettua gli stessi controlli
> di `valgrind`

A questo punto, eseguendo il programma normalmente:

        ./demo-valgrind

si ottiene un output simile a questo:

```
=================================================================
==19319==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x604000000038 at pc 0x55d2d9719328 bp 0x7ffd5de46100 sp 0x7ffd5de460f0
WRITE of size 4 at 0x604000000038 thread T0
    #0 0x55d2d9719327 in main /home/moreno/didattica/LabASD/demo-valgrind.c:259
    #1 0x7f3e0a25d082 in __libc_start_main ../csu/libc-start.c:308
    #2 0x55d2d97191cd in _start (/home/moreno/didattica/LabASD/demo-valgrind+0x11cd)

0x604000000038 is located 0 bytes to the right of 40-byte region [0x604000000010,0x604000000038)
allocated by thread T0 here:
    #0 0x7f3e0a538808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x55d2d97192ac in main /home/moreno/didattica/LabASD/demo-valgrind.c:249
    #2 0x7f3e0a25d082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/moreno/didattica/LabASD/demo-valgrind.c:259 in main
Shadow bytes around the buggy address:
  0x0c087fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c087fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c087fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c087fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c087fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c087fff8000: fa fa 00 00 00 00 00[fa]fa fa fa fa fa fa fa fa
  0x0c087fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c087fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c087fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c087fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c087fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
==19319==ABORTING
```

L'errore fa riferimento ad una operazione di scrittura che avviene al di
fuori di un'area di memoria valida. Il programma stampa sia il punto esatto
in cui avviene la scrittura:

        #0 0x55d2d9719327 in main /home/moreno/didattica/LabASD/demo-valgrind.c:259

che corrisponde all'istruzione `a[n] = 10`, sia il punto in cui è
stata allocata la regione di 40 byte al di fuori della quale si sta
tentando di scrivere:

        #1 0x55d2d97192ac in main /home/moreno/didattica/LabASD/demo-valgrind.c:249

che corrisponde alla `malloc()`.

Si noti che il programma si interrompe al primo errore incontrato.

## File

- [demo-valgrind.c](demo-valgrind.c)

***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main( void )
{
    const int n = 10;
    int *a = (int*)malloc(n*sizeof(*a));

    int b; /* ERRORE: variabile non usata; valgrind non segnala
              errori, ma il compilatore gcc con i flag -Wall
              -Wpedantic segnala un warning */

    assert(a != NULL); /* per evitare un possibile warning con VS */

    /* ERRORE: accesso out-of-bound in scrittura; l'ultimo elemento di
       a[] è a[n-1], non a[n] */
    a[n] = 10;

    /* ERRORE: accesso out-of-bound in lettura */
    printf("%d\n", a[n]);

    if (a[0] > 0) { /* ERRORE: accesso a variabile non inizializzata */
        printf("Vero\n");
    } else {
        printf("Falso\n");
    }

    /* ERRORE: non viene liberata la memoria puntata da `a` con
       free(). Questo tecnicamente non è un problema, perché il
       sistema operativo libera automaticamente tutta la memoria
       associata ad un processo dopo la terminazione, ma è comunque
       una cattiva pratica di programmazione. */

    return EXIT_SUCCESS;
}
