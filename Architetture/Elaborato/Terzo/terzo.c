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
        mov ecx, len                    // Salvo la lunghezza come contatore del ciclo
        cmp ecx, 0                      // Controllo se la lunghezza è 0
        je fine
        push ecx                        // Salvo il contatore per riprenderlo successivamente
        xor ecx, ecx
        mov cl, n
        xor edx, edx
    maschera:                           // Creo una maschera di n bit a 1 in EDX
        shl edx, 1
        inc edx
        loop maschera
        pop ecx                         // Riprendo il contatore
        lea esi, vet
    estrai_byte:
        cmp ecx, 32
        jb scorri_n
        push ecx
        shr ecx, 3                      // Divido per 8
        movbe eax, [esi + ecx - 3]      // Prendo i byte in big endian in modo da gestirli sequenzialmente
        pop ecx
    scorri_n:                           // Esegue uno shift di n bit
        push ecx
        mov cl, n
        shr eax, cl
        pop ecx
        cmp eax, 0
        je estrai_byte
    bit_parita:
        cmp errori, 1                   // Al primo errore che trova finisce il programma
        je fine
        mov ebx, eax
        and ebx, 1                      // Salva il bit di parità in EDX e scorre un bit verso destra
        shr eax, 1
    estrai_bit:
        and eax, edx                    // Controllo n bit
        cmp eax, 0
        je estrai_byte
        push ecx
        call controlla_parita
        pop ecx
        push ecx
        mov cl, n
        shr ebx, cl                     // Eseguo uno shift di n bit
        pop ecx
        loop estrai_bit
        jmp fine

    controlla_parita:
        mov cl, n
    ciclo_parita:
        cmp eax, 0
        je fine_parita
        test eax, 1                     // Controlliamo il bit se è a uno
        jne bit_zero
        or errori, 1                    // Aggiungiamo il bit di parita
    bit_zero:
        shr eax, 1
        loop ciclo_parita
    fine_parita:
        ret

    fine:
    }

    // Stampa su video
    printf("La sequenza di bit %scontiene errori\n", (errori ? "" : "non "));
}

