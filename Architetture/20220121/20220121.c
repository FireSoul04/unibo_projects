#include <stdio.h>

int main() {
	unsigned int fl = 0xc3444100;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		XOR AH, AL
		MOV BYTE PTR Vet[2], AH
		MOV BYTE PTR Vet[3], AL
		SHL WORD PTR Vet[2], 3
		MOV AX, WORD PTR Vet[2]
		MOV Ris1, AX
		// --------------------------------------
		MOV ECX, 4
		MOV AX, Mat
		SHL EAX, 16
		MOV AX, Mat
		MOV EBX, 0
		L1: MOV BYTE PTR Vet[EBX], AL
		SHR EAX, 8
		INC EBX
		LOOP L1
		PUSH WORD PTR Vet[1]
		POP Ris2
		// --------------------------------------
		MOV DX, Mat
		TEST DX, 03h; TEST si comporta come AND, ma non modifica il primo operando
		JNZ L2
		JMP L3
		L2 : NOT DX
		JMP L4
		L3 : NEG DX
		L4 : DEC DX
		XOR DX, 0FFFFh
		MOV Ris3, DX
		// --------------------------------------
		MOV AX, Mat
		AND AX, 00FFh
		OR AX, 0100h
		MOV BL, 3
		DIV BL; Divis.senza segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 7Fh
		XOR BL, BL
		MOV BL, -4
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
		ADD AX, 0Dh
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