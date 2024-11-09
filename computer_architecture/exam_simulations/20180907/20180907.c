#include <stdio.h>

int main() {
	unsigned int fl = 0x45414400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		XOR ECX, ECX
		MOV CX, Mat
		MOV AX, CX
		AND CX, 0007h
		ADD CX, 8
		SUB DX, DX
		DEC DX
		L1 : XOR AX, DX
		LOOP L1
		INC AX
		MOV Ris1, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, AH
		AND AL, 0100b
		JNZ L2
		INC AL
		JMP L3
		L2 : SUB AL, -7
		L3 : MOV Ris2, AX
		// --------------------------------------
		MOV AX, Mat
		LEA ESI, Vet
		MOV[ESI + 10], AX
		SHL AX, 4
		MOV[ESI + 12], AX
		MOV ECX, 4
		L4: MOV AH, [ESI + ECX + 9]
		MOV[ESI + ECX + 20], AH
		LOOP L4
		MOV AH, [ESI + 24]
		XOR AL, AL
		MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		AND AX, 00FFh
		OR AX, 0100h
		MOV BL, 7
		DIV BL; Divis.senza segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		MOV BL, -2
		AND BL, 6Fh
		XOR BL, 0F6h
		SHR AX, 4
		OR AL, 7
		AND AX, 007Fh
		MOV BL, -3
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
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