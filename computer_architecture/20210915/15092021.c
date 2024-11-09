#include <stdio.h>

int main() {
	float fl = -64441.8125;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		SHL AX, 2
		XOR CX, CX
		SUB CX, AX
		DEC CX
		MOV Ris1, CX
		// --------------------------------------
		MOV AX, Mat
		SUB DX, DX
		DEC DX
		AND AX, DX
		XOR AX, 33h
		MOV Ris2, AX
		// --------------------------------------
		MOV DX, Mat
		MOV ECX, 7
		MOV WORD PTR Vet[ECX * 4 + 1], DX
		MOV WORD PTR Vet[ECX * 4 + 2], DX
		MOV AX, WORD PTR Vet[ECX * 2 + 15]
		TEST AX, 1; TEST si comporta come AND, ma non modifica AX
		JNZ L1
		SHL AL, 1
		JMP L2
		L1 : SHR AL, 1
		L2 : MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		XOR AH, AH
		XOR BL, BL
		ADD BL, 3
		DIV BL; Divis.senza segno di AX per r / m8: risultato in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		MOV BL, 16
		MUL BL; Moltiplicazione senza segno di AL per r / m8: risultato in AX
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