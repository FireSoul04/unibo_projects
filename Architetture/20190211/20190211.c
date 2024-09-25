#include <stdio.h>

int main() {
	float fl = 74123.4375;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		PUSH AX
		ROL AX, 6
		PUSH AX
		POP BX
		POP DX
		MOV Ris1, DX
		// --------------------------------------
		MOV AX, Mat
		MOV BX, AX
		AND AX, 0ff01h
		AND BX, 10ffh
		ADD AX, BX
		DEC AX
		MOV Ris2, AX
		// --------------------------------------
		MOV AX, Mat
		LEA ESI, Vet
		MOV[ESI + 3], AX
		SHL AX, 4
		MOV[ESI + 5], AX
		MOV ECX, 4
		L3: MOV AL, [ESI + ECX + 2]
		MOV[ESI + ECX + 12], AL
		LOOP L3
		MOV AL, [ESI + 16]
		MOV DX, AX
		SUB AL, AL
		MOV AH, DL
		MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 0000fff1h
		MOV BL, -3
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		PUSH AX
		POP Ris4
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 00000001h
		AND EAX, 0000000fh
		XOR BX, BX
		SUB BX, 251
		MUL BL; Molt.senza segno di AL per r / m8: ris.in AX
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