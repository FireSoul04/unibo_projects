#include <stdio.h>

int main() {
	unsigned int fl = 0x44144400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV CX, Mat
		AND CX, 00FFh
		PUSH CX
		OR CX, 1000h
		PUSH CX
		OR CX, 0303h
		POP BX
		ADD CX, BX
		POP BX
		XOR CX, BX
		MOV Ris1, CX
		// --------------------------------------
		MOV AX, Mat
		XOR AH, AL
		TEST AH, 4
		JNZ L1
		SUB AH, 3
		JMP L2
		L1 : INC AH
		L2 : MOV Ris2, AX
		// --------------------------------------
		MOV AX, Mat
		MOV BYTE PTR Vet[10], AL
		MOV BYTE PTR Vet[15], 23
		MOV BYTE PTR Vet[20], AH
		MOV BYTE PTR Vet[25], 49
		LEA ESI, Vet
		ADD ESI, 8
		XOR EBX, EBX
		MOV ECX, 4
		L3: XOR BL, [ESI + 2]
		ADD ESI, 5
		LOOP L3
		MOV Ris3, BX
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 0000FFF1h
		MOV BL, -3
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		MOV BL, 4
		SHL AX, 1
		JC L4
		INC BL
		L4 : MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
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