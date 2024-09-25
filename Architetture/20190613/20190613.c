#include <stdio.h>

int main() {
	float fl = 24157.9375;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		PUSH Mat
		XOR ECX, ECX
		POP CX
		ADD CX, 365
		MOV EAX, ECX
		SHL EAX, 7
		XOR AH, AL
		MOV DX, AX
		OR DL, CH
		MOV Ris1, DX
		INC Ris1
		// --------------------------------------
		MOV DX, Mat
		XOR DX, 0F0Fh
		MOV WORD PTR Vet[63], DX
		INC DX
		MOV WORD PTR Vet[31], DX
		MOV BX, Mat
		AND EBX, 2h
		OR EBX, 2h
		SHL EBX, 5
		DEC EBX
		MOV AX, WORD PTR Vet[EBX]
		MOV Ris2, AX
		// --------------------------------------
		MOV AX, Mat
		MOV BYTE PTR Vet[10], AL
		MOV BYTE PTR Vet[13], 99
		MOV BYTE PTR Vet[16], AH
		LEA ESI, Vet
		ADD ESI, 9
		XOR EBX, EBX
		MOV ECX, 3
		l1: XOR BL, [ESI + 1]
		ADD ESI, 3
		LOOP l1
		MOV Ris3, BX
		// --------------------------------------
		MOV AX, Mat
		XOR AH, AH
		XOR BL, BL
		ADD BL, 6
		DIV BL; Divis.senza segno di AX per r / m8: risultato in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 6Fh
		XOR BL, BL
		MOV BL, -4
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
		MOV Ris5, AX
	}

	printf("FL: %x\n", *(unsigned int*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}