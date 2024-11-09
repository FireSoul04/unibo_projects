#include <stdio.h>

int main() {
	float fl = 54441.8125;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		PUSH Mat
		XOR ECX, ECX
		POP CX
		ADD CX, 300
		MOV EAX, ECX
		SHL EAX, 8
		XOR AH, AL
		MOV DX, AX
		OR DL, CH
		MOV Ris1, DX
		INC Ris1
		// --------------------------------------
		MOV AX, Mat
		NOT AX
		AND AL, 08h
		JZ L1
		OR AH, 6Fh
		JMP L2
		L1 : XOR AH, 54h
		L2 : MOV Ris2, AX
		// --------------------------------------
		MOV DX, Mat
		MOV ECX, 7
		MOV WORD PTR Vet[ECX * 2 + 1], DX
		MOV WORD PTR Vet[ECX * 2 + 2], DX
		MOV AX, WORD PTR Vet[ECX + 8]
		TEST AX, 1; TEST si comporta come AND, ma non modifica AX
		JNZ L3
		SHL AL, 1
		JMP L4
		L3 : SHR AL, 1
		L4 : MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		MOV CX, AX
		SHR AX, 7
		MOV BL, 1
		SHL BL, 4
		MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
		SUB CX, AX
		MOV Ris4, CX
		// --------------------------------------
		MOV AX, Mat
		OR AX, 0FFF0h
		MOV BL, -2
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		PUSH AX
		POP Ris5
	}

	printf("FL: %x\n", *(unsigned int*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}