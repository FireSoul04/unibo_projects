#include <stdio.h>

int main() {
	unsigned int fl = 0xc4144400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		XOR EAX, EAX
		MOV DX, Mat
		DEC DX
		MOV AX, Mat
		SHL EDX, 16
		OR EDX, EAX
		BSWAP EDX; Converte little - endian / big - endian
		ROL DX, 2
		MOV Ris1, DX
		// --------------------------------------
		MOV CX, Mat
		MOV BX, CX
		XOR CX, 0F0F0h
		XOR CX, 00F0Fh
		NEG CX
		OR CX, 4
		AND CX, 000Fh
		ROL BX, CL
		MOV Ris2, BX
		// --------------------------------------
		MOV AX, Mat
		MOV BYTE PTR Vet[10], AL
		MOV BYTE PTR Vet[13], 99
		MOV BYTE PTR Vet[16], AH
		LEA ESI, Vet
		ADD ESI, 9
		XOR EBX, EBX
		MOV ECX, 3
		L1: XOR BL, [ESI + 1]
		ADD ESI, 3
		LOOP L1
		MOV Ris3, BX
		// --------------------------------------
		MOV AX, Mat
		MOV BL, 7
		SHL AX, 1
		JC L2
		INC BL
		L2 : MUL BL; Moltiplic.senza segno di AL per r / m8: ris.in AX
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		OR AX, 0FFF1h
		MOV BL, -4
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		PUSH AX
		POP Ris5
	}

	printf("FL: %f\n", *(float*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}