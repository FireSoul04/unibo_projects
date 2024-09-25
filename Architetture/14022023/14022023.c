#include <stdio.h>

int main() {
	unsigned int fl = 0x43144400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV DX, Mat
		AND DX, 00EFh
		XOR ECX, ECX
		MOV CX, DX
		OR CX, 4
		L1: INC DX
		NEG DX
		LOOP L1
		MOV Ris1, DX
		// --------------------------------------
		MOV AX, Mat
		XOR AH, AL
		TEST AH, 4
		JNZ L2
		SUB AH, 3
		JMP L3
		L2 : INC AH
		L3 : MOV Ris2, AX
		// --------------------------------------
		MOV DX, Mat
		MOV ECX, 9
		MOV WORD PTR Vet[ECX * 4 + 1], DX
		MOV WORD PTR Vet[ECX * 4 + 2], DX
		MOV AX, WORD PTR Vet[ECX * 2 + 19]
		TEST AX, 1; TEST si comporta come AND, ma non modifica AX
		JNZ L4
		SHL AL, 1
		JMP L5
		L4 : SHR AL, 1
		L5 : MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 0000FFF1h
		MOV BL, -3
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		PUSH AX
		POP Ris4
		// --------------------------------------
		XOR ECX, ECX
		MOV BL, 2
		MOV AX, Mat
		AND AX, 3
		OR AX, 2
		MOV CX, AX
		L6 : MUL BL; Molt.senza segno di AL per r / m8:risultato in AX
		LOOP L6
		MOV AH, AL
		NEG AH
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