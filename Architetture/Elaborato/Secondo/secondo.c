
/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 2
 Descrizione: Calcolare la matrice di DWORD prodotto di due matrici di WORD.
              Le matrici sono memorizzate per righe all’interno di array
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
        cmp edx, n
        jb terzo_ciclo
    fine_terzo_ciclo:
        inc ecx
        cmp ecx, m
        jb secondo_ciclo
    fine_secondo_ciclo:
        inc ebx
        cmp ebx, k
        jb primo_ciclo
    fine_primo_ciclo:
        jmp fine

    // Esegue il prodotto riga per colonna di mat1 e mat2 per salvarlo in mat3
    prodotto_riga_per_colonna:
        push edx
        mov eax, ecx
        mul n
        pop edx
        add eax, edx                    // Cambio colonna di mat1
        push edx
        mov ax, [esi + eax * 2]         // Salvo in AX la cella nell'indice calcolato nel prodotto precedente
        push ax
        mov eax, edx
        mul k
        add eax, ebx                    // Cambio colonna di mat2
        mov edx, eax
        xor eax, eax
        pop ax
        imul word ptr [edi + edx * 2]   // Moltiplico le celle
        shl edx, 16                     // Sposto il risultato della moltiplicazione nella word alta DX di 16 bit
        add eax, edx                    // Aggiungo alla word alta di EAX la word DX
        push eax
    somma_a_cella:
        mov eax, ecx
        mul k
        add eax, ebx                    // Cambio colonna di mat3
        mov edx, eax
        pop eax
        add [mat3 + edx * 4], eax
        pop edx
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


