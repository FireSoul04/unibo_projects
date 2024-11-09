#include <stdio.h>

int main() {
	unsigned int fl = 0xc6441400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		MOV BX, AX
		AND BX, 4BFFh
		INC BX
		SUB AX, BX
		DEC AX
		MOV Ris1, AX
		// --------------------------------------
		MOV DX, Mat
		XCHG DL, DH; scambia il contenuto dei due registri
		MOV WORD PTR Vet[90], DX
		ROR BYTE PTR Vet[91], 5
		PUSH WORD PTR Vet[90]
		POP Ris2
		// --------------------------------------
		MOV AX, Mat
		LEA ESI, Vet
		MOV[ESI + 3], AX
		SHL AX, 4
		MOV[ESI + 5], AX
		MOV ECX, 8
		SHR ECX, 1
		L1: MOV AL, [ESI + ECX + 2]
		MOV[ESI + ECX + 12], AL
		LOOP L1
		MOV AL, [ESI + 16]
		PUSH AX
		SUB AL, AL
		POP DX
		MOV AH, DL
		MOV Ris3, AX
		// --------------------------------------
		XOR ECX, ECX
		MOV BL, 2
		MOV AX, Mat
		AND AX, 3
		OR AX, 2
		MOV CX, AX
		L2 : MUL BL; Moltiplicazione senza segno di AL per r / m8:risultato in AX
		LOOP L2
		MOV AH, AL
		NEG AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 0000FFF1h
		MOV BL, -3
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		PUSH AX
		POP Ris5
	}

	printf("FL: %f\n", *(float*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}