#include <stdio.h>

int main() {
	float fl = 2441.6875;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		ROR AX, 5
		ADD AX, -10
		XOR AX, 0FFFEh
		MOV Ris1, AX
		// --------------------------------------
		MOV BX, Mat
		MOV CX, BX
		NEG BX
		XOR BX, 00F0Fh
		XOR BX, 0F0F0h
		NOT BX
		OR CX, 4
		AND CX, 000Eh
		ROL BX, CL
		MOV Ris2, BX
		// --------------------------------------
		MOV DX, Mat
		MOV ECX, 5
		MOV WORD PTR Vet[ECX * 4 + 3], DX
		MOV WORD PTR Vet[ECX * 4 + 5], DX
		MOV AX, WORD PTR Vet[ECX * 2 + 14]
		TEST AX, 1; TEST si comporta come AND, ma non modifica AX
		JNZ L1
		SHL AL, 2
		JMP L2
		L1 : SHR AL, 3
		L2 : MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		AND AX, 00FFh
		OR AX, 0100h
		MOV BL, 5
		DIV BL; Divis.senza segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 7Fh
		XOR BL, BL
		MOV BL, -3
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
		ADD AX, 0Dh
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