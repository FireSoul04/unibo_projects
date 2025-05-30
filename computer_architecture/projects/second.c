
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Calcolare la matrice di DWORD prodotto di due matrici di WORD.
              Le matrici sono memorizzate per righe all�interno di array
              monodimensionali. Gli elementi delle matrici sono da considerarsi
              con segno (in complemento a due).
 ********************************************************************************/

#include <stdio.h>


void main()
{
    unsigned int m = 3; // numero di righe della prima matrice
    unsigned int n = 2; // numero di colonne della prima matrice
    unsigned int k = 4; // numero di colonne della seconda matrice
    short int mat1[] = { 
        -1,-2, 
         4, 5, 
         4,-2 
    }; // prima matrice
    short int mat2[] = { 
        2,0,0,0, 
        0,2,0,0 
    }; // seconda matrice
    int mat3[1024]; // matrice risultato

    __asm {
        // Azzera il contenuto da riservare a mat3
        mov eax, m
        mul k                           // Lunghezza effettiva della matrice risultato
        mov ecx, eax
        lea esi, mat3
    inizializza_matrice:
        xor eax, eax
        mov [esi + ecx * 4 - 4], eax
        loop inizializza_matrice

    inizio:
        lea esi, mat1
        lea edi, mat2
        xor ebx, ebx                    // Colonna di mat2
    primo_ciclo:
        xor ecx, ecx                    // Riga di mat1
    secondo_ciclo:
        xor edx, edx                    // Colonna di mat1
    terzo_ciclo:                        // Salvo tutti i contatori per non perderli durante i prodotti
        push ebx
        push ecx
        push edx
        call prodotto_riga_per_colonna
        pop edx
        pop ecx
        pop ebx
        inc edx
        cmp edx, n                      // Continuo finch� non scorre n righe di mat1
        jb terzo_ciclo
    fine_terzo_ciclo:
        inc ecx
        cmp ecx, m                      // Continuo finch� non scorre m colonne di mat1
        jb secondo_ciclo
    fine_secondo_ciclo:
        inc ebx
        cmp ebx, k                      // Continuo finch� non scorre k colonne di mat2
        jb primo_ciclo
    fine_primo_ciclo:
        jmp fine

    // Esegue il prodotto riga per colonna di mat1 e mat2 per salvarlo in mat3
    prodotto_riga_per_colonna:
        push edx                        // Salvo EDX per non perderlo
        mov eax, ecx
        mul n                           // Cambio riga di mat1
        pop edx
        add eax, edx                    // Cambio colonna di mat1
        mov ax, [esi + eax * 2]         // Salvo in AX la cella nell'indice calcolato nel prodotto precedente
        push ax                         // Salvo la cella di mat1 nello stack
        mov eax, edx
        mul k                           // Cambio riga di mat1
        add eax, ebx                    // Cambio colonna di mat2
        mov edx, eax
        xor eax, eax                    // Azzero EAX in modo da non avere valori sconosciuti nella word alta quando faccio il pop
        pop ax
        imul word ptr [edi + edx * 2]   // Riprendo la cella di mat1 per moltiplicarla con quella di mat2
        shl edx, 16                     // Sposto il risultato della moltiplicazione nella word alta DX di 16 bit
        add eax, edx                    // Aggiungo alla word alta di EAX la word DX
        push eax                        // Salvo il risultato della moltiplicazione delle due celle
    somma_a_cella:
        mov eax, ecx
        mul k                           // Cambio riga di mat3
        add eax, ebx                    // Cambio colonna di mat3
        mov edx, eax
        pop eax                         // Riprendo il risultato della precedente moltiplicazione delle celle
        add [mat3 + edx * 4], eax       // Sommo il risultato della moltiplicazione con i risultati di moltiplicazioni precedenti
        ret

    fine:
    }

    // Stampa su video
    {
        unsigned int i, j, h;
        printf("Matrice prodotto:\n");
        for (i = h = 0; i < m; i++)
        {
            for (j = 0; j < k; j++, h++)
                printf("%6d ", mat3[h]);
            printf("\n");
        }
    }
}


