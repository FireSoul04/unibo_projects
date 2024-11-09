//#include <stdio.h>
//
//int main() {
//	unsigned int fl = 0xC7414400;
//	unsigned short int Mat = 4441;
//	unsigned char Vet [100];
//	unsigned short Ris1,Ris2,Ris3,Ris4,Ris5;
//
//	__asm {
//		MOV AX, Mat
//		SUB DX, DX
//		DEC DX
//		AND AX, DX
//		XOR AX, 7Dh
//		MOV Ris1, AX
//	// --------------------------------------
//		MOV AX, Mat
//		NEG AH
//		NEG AL
//		ADD AH, AL
//		NEG AH
//		NEG AL
//		MOV Ris2, AX
//	// --------------------------------------
//		XOR ECX, ECX
//		MOV BX, Mat
//		MOV AX, BX
//		MOV CX, AX
//		AND CX, 0Fh
//		OR CX, 03h
//		LEA ESI, Vet
//		ADD ESI, ECX
//		MOV[ESI], BX
//		ADD ESI, 2
//		MOV[ESI], BX
//		INC ECX
//		OR AX, WORD PTR Vet[ECX]
//		MOV Ris3, AX
//	// --------------------------------------
//		MOV AX, Mat
//		OR EAX, 0000FFF1h
//		MOV BL, -5
//		IDIV BL				; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
//		PUSH AX
//		POP Ris4
//	// --------------------------------------
//		MOV AX, Mat
//		MOV CX, AX
//		SHR AX, 8
//		MOV BL, 1
//		SHL BL, 3
//		MUL BL				; Moltiplic.senza segno di AL per r / m8: ris.in AX
//		SUB CX, AX
//		MOV Ris5, CX
//	}
//
//	printf("FL: %f\n", *(float *)&fl);
//	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
//	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
//	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
//	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
//	printf("Ris5: %hx, %hd\n", Ris5, Ris5);
//
//
//	return 0;
//}

#include <stdio.h>

void main()
{
    unsigned char vet[] = { 18, 173, 24 };
    unsigned int len = 21; // lunghezza (numero di bit)
    unsigned char n = 6; // numero di bit dati

    //Output
    unsigned char errori = 0; // 1 = errori; 0 = no errori

    __asm
    {
        MOV EAX, len
        CMP EAX, 0
        JLE INIZIO_2
        CDQ
        MOV EBX, 8
        DIV EBX
        MOV AH, n
    INIZIO_1 :
        XOR EAX, EAX
        XOR ESI, ESI
        XOR EBX, EBX
        XOR ECX, ECX
        XOR EDX, EDX
    INIZIO_2 :
        MOV EDI, 1

        /*
        Imposto un registro di 8 bit al byte corrente
        Questa etichetta verrà chiamata ogni volta che si dovrà elaborare il nuvo byte corrente
        */
    ELABORAZIONE_BYTE_CORRENTE:
        MOV AL, vet[ESI]
        MOV AH, n
        MOV DL, -1

        /*
        Confronto il contatore dei bit DL con il numero dei dati n
        Se sono uguali, allora salto per controllare la parità
        Altrimenti incremento DH, che ho scelto come contatore dei bit scorsi
        e lo confronto con 8 , che è il numero di bit in un byte
        Se risulterà uguale significache ho finito di controllare il byte corrente e vado al prossimo
        */
    SCORRIMENTO_BIT:
        INC DL
        CMP DL, AH
        JE VERIFICA_PARITA_CONTEGGIO_BIT
        INC DH
        CMP DH, 8
        JE INCREMENTO_INDICE_VETTORE

        /*
        Se invece non sono uguali devo continaure a processari i bit del byte corrente
        Quindi salto a CONTROLLO_BIT_MENO_SIGNIFICATIVO dove effettuo un operazione AND per ottenere
        il valore del bit meno significativo
        Se non è 1 continuo a scorrere i bit
        */
        CALL CONTROLLO_BIT_MENO_SIGNIFICATIVO
        JNE SCORRIMENTO_BIT
        /*
        Altrimenti incremento il contatore dei bit a 1, che ho scelto come CL e continuo sempre
        a scorrere
        */
        INC CL
        JMP SCORRIMENTO_BIT

        /*
        Successivamente incremento l'indice del vetttore
        E lo confronto con EDI per vedere se sono alla gine.
        Se si salto a END
        Senno' azzero il contatore dei bit scorsi decremento DL perché il ciclo per lo scorrimento
        dei bit lo incrementa
        */
    INCREMENTO_INDICE_VETTORE:
        INC ESI
        CMP ESI, EDI
        //JE END
        XOR DH, DH
        DEC DL
        JMP ELABORAZIONE_BYTE_CORRENTE

        /*
        Questa etichetta che viene chiamata quando il contatore dei bit fino a n è uguale al numero
        di bit dati n, e attua una verifica sulla parità
        Inanzitutto compara il contatore dei bit a 1 con 8 se non è uguale salta ad avanti nel processamento
        continuando dunque ad esaminare i bit nel byte corrente
        Se è uguale lo confronta con AH, che è n
        */
    VERIFICA_PARITA_CONTEGGIO_BIT:
        CMP DH, 8
        JNE AVANTI_NELL_ELABORAZIONE
        CMP DL, AH
        /*
        Se non sono ancora uguali continua sempre ad esaminare i bit
        Per poi passare andare al prossimo byte
        */
        JNE AVANTI_NELL_ELABORAZIONE
        JMP PROSSIMO_BYTE


    AVANTI_NELL_ELABORAZIONE :
        CALL CALCOLA_PARITA
        JE NO_ERRORE
        CMP BH, 0
        JE NO_ERRORE
        /*
        Se il valore in BH è 2 oppure 0 allora i bit di parità non presentano errori
        Quindi si salta a NO_ERRORE
        Altrimenti vi è un errore
        */
        JMP ERRORE

        /*
        Resetto il contatore dei bit e il contatore dei bit a 1
        */
    RESET_REGISTRI:
        XOR DL, DL
        XOR CL, CL
        ret

    SHIFT_E_INCREMENTA :
        /*
        Shifto il byte a destra di 1 e
        incremento il contatore dei bit scorsi
        */
        SHR AL, 1
        INC DH

    NO_ERRORE :
        call RESET_REGISTRI
        CMP DH, 8
        /*
        Se è uguale a 8 allora ho terminato il byte e
        incremento indice del vettore ritornando a
        riscorrere dei bit
        */
        JE INCREMENTO_INDICE_VETTORE
        JMP SCORRIMENTO_BIT

        /*

        */
    PROSSIMO_BYTE:
        INC ESI
        CMP ESI, EDI
        /*
        Se il vettore è terminato salto ad end
        senno contnuo a processare il byte successivo
        */
        JE END
        MOV AL, vet[ESI]
        XOR DH, DH
        JMP AVANTI_NELL_ELABORAZIONE

        /*
        La seguente etichetta è spiegata sopra
        */
    CONTROLLO_BIT_MENO_SIGNIFICATIVO:
        MOV BL, 1
        AND BL, AL
        SHR AL, 1
        CMP BL, 1
        RET

        /*
        La seguente etichetta è spiegata sopra
        */
    CALCOLA_PARITA:
        MOV BL, 1
        AND BL, CL
        MOV BH, 1
        AND BH, AL
        ADD BH, BL
        CMP BH, 2
        RET

        /*
        Incremento errori e finisco
        */
    ERRORE:
        MOV errori, 1
    END :
    }

    // Stampa su video
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //11100010
            unsigned char bit = (vet[i] & (0b10000000 >> j)) != 0 ? 1 : 0;
            printf("%d", bit);
        }
    }
    printf("\nLa sequenza di bit %s contiene errori\n", (errori ? "" : "non"));
}