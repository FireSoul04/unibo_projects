#include <stdio.h>

int main() {
	float fl = -2441.6875;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		MOV BX, Mat
		SUB BX, AX
		DEC BX
		XOR AX, BX
		NEG AX
		MOV Ris1, AX
		// --------------------------------------
		MOV AX, Mat
		LEA ESI, Vet
		ADD ESI, 5
		MOV ECX, 4
		L1: MOV[ESI + ECX * 2], AX
		LOOP L1
		LEA ESI, Vet
		ADD ESI, 9
		MOV DX, [ESI]
		SHR DX, 4
		MOV Ris2, DX
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
		OR AX, 0FF00h
		XOR BL, BL
		SUB BL, 4
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 079h
		OR AL, 0A0h
		XOR BL, BL
		DEC BL
		DEC BL
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