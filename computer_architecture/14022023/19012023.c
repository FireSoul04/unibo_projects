#include <stdio.h>

int main() {
	unsigned int fl = 0xc5441400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		XCHG AL, AH; scambia il contenuto dei due registri
		MOV WORD PTR Vet[10], AX
		ROR BYTE PTR Vet[11], 4
		PUSH WORD PTR Vet[10]
		POP Ris1
		// --------------------------------------
		MOV DX, Mat
		SHL DX, 1
		JNC L1
		ROL DX, 1
		L1: NEG DX
		MOV AX, DX
		MOV Ris2, AX
		ADD Ris2, DX
		// --------------------------------------
		LEA ESI, Vet
		ADD ESI, 7
		MOV AX, Mat
		NEG AX
		SHL EAX, 16
		MOV AX, Mat
		BSWAP EAX; Converte little - endian / big - endian
		MOV DWORD PTR[ESI], EAX
		INC ESI
		MOV DX, [ESI]
		MOV Ris3, DX
		// --------------------------------------
		MOV AX, Mat
		XOR AH, AH
		XOR BL, BL
		ADD BL, 5
		DIV BL; Divis.senza segno di AX per r / m8: risultato in AL, resto in AH
		MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 70h
		OR AL, 8Fh
		XOR BL, BL
		SUB BL, 9
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
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