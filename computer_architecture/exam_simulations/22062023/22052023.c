#include <stdio.h>

int main() {
	unsigned int fl = 0xc4441400;
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
		ROL DX, 6
		MOV Ris1, DX
		// --------------------------------------
		MOV AX, Mat
		AND AX, 00FFh
		NEG AX
		MOV CX, -5
		SUB AX, CX
		MOV Ris2, AX
		// --------------------------------------
		MOV AX, Mat
		MOV DL, AL
		NOT DL
		MOV ECX, 100
		L1: MOV BYTE PTR Vet[ECX - 1], DL
		LOOP L1
		AND DL, 0Fh
		ADD DL, 7
		XOR EBX, EBX
		MOV BL, DL
		MOV WORD PTR Vet[EBX], AX
		MOV ECX, 96
		L2: CMP WORD PTR Vet[ECX], AX
		JE L3
		LOOP L2
		L3 : MOV CH, CL
		NOT CL
		MOV Ris3, CX
		// --------------------------------------
		XOR ECX, ECX
		MOV BL, 3
		MOV AX, Mat
		AND AX, 3
		OR AX, 2
		MOV CX, AX
		L4 : MUL BL; Moltiplicazione senza segno di AL per r / m8:risultato in AX
		LOOP L4
		MOV AH, AL
		NOT AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		OR AX, 0FFF1h
		MOV BL, -3
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
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