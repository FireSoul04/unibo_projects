/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 3
 Descrizione:	Data una sequenza di bit, sapendo che ogni n bit (di dati) vi è
                un bit di parità (1 se il numero di bit a 1 fra i precedenti nè
                dispari), verificare se vi sono errori.

 ********************************************************************************/

#include <stdio.h>

void main()
{
    // Input
    unsigned char vet[] = { 2,4,67,2,2,58,99 };
    unsigned int len = 55;	// lunghezza (numero di bit)
    unsigned char n = 4;	// numero di bit dati

    // Ouput
    unsigned char errori = 0;	// 1 = errori; 0 = no errori

    __asm {
        mov ebx, len                    // Salvo la lunghezza come contatore del ciclo
        cmp ebx, 0                      // Controllo se la lunghezza è 0
        je fine
        mov ch, 8                       // Contatore per gestire quando passare al prossimo byte
        lea esi, vet                    // Salvo in ESI il puntatore del primo byte
        mov al, [esi]
    ciclo:
        cmp errori, 1                   // Al primo errore che trova finisce il programma
        je fine
        xor ah, ah                      // Azzero il bit di parità di un blocco
        mov cl, n
    estrai_bit:
        test al, 1
        jz pari                         // Se l'and restituisce 0 AH è pari e non aggiungo un bit alla parità
        xor ah, 1                       // Conto la parità in AH, uso l'XOR per evitare di gestire la carry
    pari:
        shr al, 1
    segui_byte:
        dec ebx
        cmp ebx, 0                      // Controllo quando ho finito di scorrere i bit
        je fine
        call controlla_byte
        dec cl
        cmp cl, 0
        jg estrai_bit
    bit_parita:
        mov dl, al
        and dl, 1                       // Salvo il bit di parità in DL
        shr al, 1                       // Passo al primo bit del blocco
        call controlla_parita
        call controlla_byte
        dec ebx
        cmp ebx, 0                      // Controllo quando ho finito di scorrere i bit
        je fine
        jmp ciclo

    // Confronto il bit di parità con la parità del blocco di bit
    controlla_parita:
        cmp ah, dl
        je fine_controllo
        or errori, 1                    // Se la parità dei bit e il bit di parità sono uguali inizializzo errori a 1
    fine_controllo:
        ret

    // Controlla se devo controllare il prossimo byte del vettore
    controlla_byte:
        dec ch                          // Contatore di bit, quando arriva a 0 passo al byte successivo
        cmp ch, 0
        jg fine_controllo_byte
        inc esi                         // Passo al prossimo byte
        mov ch, 8
        mov al, [esi]                   // Prende il byte successivo
    fine_controllo_byte:
        ret

    fine:
    }

    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
}

