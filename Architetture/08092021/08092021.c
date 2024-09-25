#include <stdio.h>

int main() {
	float fl = -94441.1875;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV CX, Mat
		MOV BX, CX
		XOR CX, 00F0Fh
		XOR CX, 0F0F0h
		NOT CX
		OR CX, 2
		AND CX, 0Fh
		ROL BX, CL
		MOV Ris1, BX
		// --------------------------------------
		XOR EAX, EAX
		MOV DX, Mat
		DEC DX
		MOV AX, Mat
		SHL EDX, 16
		OR EDX, EAX
		BSWAP EDX; Converte little - endian / big - endian
		ROL DX, 2
		MOV Ris2, DX
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
		POP Ris3
		// --------------------------------------
		MOV AX, Mat
		OR AX, 0FF00h
		XOR BL, BL
		ADD BL, 4
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		MOV CX, AX
		SHR AX, 8
		MOV BL, 1
		SHL BL, 3
		MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
		SUB CX, AX
		MOV Ris5, CX
	}

	printf("FL: %x\n", *(unsigned int*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}