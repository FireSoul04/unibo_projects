#include <stdio.h>

int main() {
	float fl = -3441.5625;
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
		ADD ESI, 7
		MOV ECX, 6
		L1: MOV[ESI + ECX * 2], AX
		LOOP L1
		LEA ESI, Vet
		ADD ESI, 9
		MOV DX, [ESI]
		SHR DX, 4
		MOV Ris2, DX
		// --------------------------------------
		MOV DX, Mat
		MOV ECX, 9
		MOV WORD PTR Vet[ECX * 4 + 1], DX
		MOV WORD PTR Vet[ECX * 4 + 2], DX
		MOV AX, WORD PTR Vet[ECX * 2 + 19]
		TEST AX, 1; TEST si comporta come AND, ma non modifica AX
		JNZ L2
		SHL AL, 1
		JMP L3
		L2 : SHR AL, 1
		L3 : MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		OR AX, 0FF00h
		XOR BL, BL
		SUB BL, 4
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 7h
		ADD AL, 7
		XOR BL, BL
		ADD BL, AH
		AND BL, 3
		ADD BL, 3
		MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
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