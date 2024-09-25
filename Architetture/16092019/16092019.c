#include <stdio.h>

int main() {
	unsigned int fl = 0x43441400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		SUB DX, DX
		DEC DX
		AND AX, DX
		XOR AX, 6Fh
		MOV Ris1, AX
		// --------------------------------------
		MOV AX, Mat
		NEG AH
		NEG AL
		ADD AH, AL
		NEG AH
		NEG AL
		MOV Ris2, AX
		// --------------------------------------
		XOR ECX, ECX
		MOV BX, Mat
		MOV AX, Mat
		MOV CX, Mat
		AND CX, 0Fh
		OR CX, 03h
		LEA ESI, Vet
		ADD ESI, ECX
		MOV[ESI], BX
		ADD ESI, 2
		MOV[ESI], BX
		INC ECX
		OR AX, WORD PTR Vet[ECX]
		MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 0000FFF1h
		MOV BL, -4
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		MOV CX, AX
		SHR AX, 8
		MOV BL, 1
		SHL BL, 3
		MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
		SUB CX, AX
		MOV Ris5, CX
	}

	printf("FL: %f\n", *(float*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}