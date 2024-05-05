
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
        mov eax, m
        mul k                           // Lunghezza effettiva della matrice risultato
        mov ecx, eax
    inizializza_matrice:
        xor eax, eax
        mov [mat3 + ecx * 4 - 4], eax
        loop inizializza_matrice
    inizio:
        xor ebx, ebx                    // Colonna di mat2
    primo_ciclo:
        xor ecx, ecx                    // Indice della cella di mat1 (indicata come indice di array tradizionale)a
    secondo_ciclo:
        xor edx, edx                    // Indice della cella di mat2 (indicata come riga * m + colonna)
    terzo_ciclo:                        // Salvo tutti i contatori per non perderli durante i prodotti
        push edx
    prodotto_riga_per_colonna:
        add edx, ebx                    // Cambio colonna di mat2
        mov ax, [mat2 + edx * 2]        // Salvo in AX la cella nell'indice calcolato nel prodotto precedente
        imul word ptr [mat1 + ecx * 2]
        shl edx, 16                     // Sposto il risultato della moltiplicazione nella word alta DX di 16 bit
        add eax, edx                    // Aggiungo alla word alta di EAX la word DX
        pop edx
        add edx, ebx                    // Cambio colonna di mat3
        add [mat3 + edx * 4], eax
        add edx, k
        inc ecx
        mov eax, n
        push edx
        mul k
        pop edx
        cmp edx, eax                    // Continuo il ciclo finché non finisco di scorrere le righe di mat2
        jb terzo_ciclo
    fine_terzo_ciclo:
        push edx
        mov eax, m
        mul n
        pop edx
        cmp ecx, eax                   // Rincomincio il ciclo quando l'indice ECX ha visto ogni dato della matrice
        jb secondo_ciclo
    fine_secondo_ciclo:
        inc ebx
        cmp ebx, k
        jb primo_ciclo
    fine_primo_ciclo:
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


