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
        lea esi, vet
    estrai_byte:
        sub ch, n
        dec ch
        cmp ch, 0
        jg ottieni_byte
        inc esi                         // Passo al prossimo byte
        mov ch, 8                       // Il contatore torna a 8
    ottieni_byte:
        mov al, [esi]
        mov cl, n
        cmp al, 0
        je estrai_byte
    bit_parita:
        //cmp errori, 1                   // Al primo errore che trova finisce il programma
        //je fine
        mov dl, al
        and dl, 1                       // Salvo il bit di parità in DL
    estrai_bit:
        cmp al, 0
        je estrai_byte                  // Quando non sono presenti bit a uno passo al prossimo blocco di bit
        dec ebx
        cmp ebx, 0                      // Controllo quando ho finito di scorrere i bit
        je fine
        mov ah, al
        and ah, 1 
        xor ah, 1                       // Conto la parità in AH, uso l'XOR per evitare di gestire la carry
        shr al, 1
        dec cl
        cmp cl, 0
        jg estrai_bit
        call controlla_parita
        jmp fine

    controlla_parita:
        cmp ah, dl
        je fine_controllo               // Se la parità dei bit e il bit di parità sono uguali inizializzo errori a 1
        or errori, 1
    fine_controllo:
        ret

    fine:
    }

    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
}

