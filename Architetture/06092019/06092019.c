#include <stdio.h>

int main() {
	unsigned int fl = 0xc4144400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		OR AX, 0A0Bh
		ROR AX, 5
		ADD AX, -8
		MOV Ris1, AX
		// --------------------------------------
		XOR EBX, EBX
		MOV AX, Mat
		MOV ECX, 8
		L1: TEST AX, 1; Imposta i flag come AND, ma non modifica l'operando
		JZ L2
		INC EBX
		L2 : SHR AX, 1
		LOOP L1
		MOV Ris2, BX
		// --------------------------------------
		MOV AX, Mat
		MOV BYTE PTR Vet[10], AL
		MOV BYTE PTR Vet[13], 99
		MOV BYTE PTR Vet[16], AH
		LEA ESI, Vet
		ADD ESI, 9
		XOR EBX, EBX
		MOV ECX, 3
		L3: XOR BL, [ESI + 1]
		ADD ESI, 3
		LOOP L3
		MOV Ris3, BX
		// --------------------------------------
		MOV BX, Mat
		AND BX, 00F0h
		PUSH BX
		SHR BL, 1
		MOV AL, 2
		MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
		POP CX
		SUB CX, BX
		MOV Ris4, CX
		// --------------------------------------
		MOV AX, Mat
		OR AX, 0FF00h
		MOV BL, -3
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris5, AX
	}

	printf("FL: %f\n", *(float*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}