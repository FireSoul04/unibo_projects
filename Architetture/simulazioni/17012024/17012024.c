#include <stdio.h>

int main() {
	unsigned int fl = 0xc4444100;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX,Mat
		MOV BX,AX
		SHR BX,4
		NEG BX
		MOV Ris1,BX
	// --------------------------------------
		MOV DX,Mat
		XCHG DL,DH ; scambia il contenuto dei due registri
		MOV WORD PTR Vet[76],DX
		ROR BYTE PTR Vet[77],3
		PUSH WORD PTR Vet[76]
		POP Ris2
	// --------------------------------------
		LEA ESI,Vet
		MOV AX,Mat
		MOV ECX,16
	L1: MOV BL,AL
		AND BL,3
		MOV BYTE PTR Vet[ECX],BL
		SHR AX,2
		LOOP L1
		MOV AX,WORD PTR Vet[14]
		MOV DX,WORD PTR Vet[12]
		SHL DX,4
		OR AX,DX
		MOV Ris3,AX
	// --------------------------------------
		MOV AX,Mat
		OR AX,0FF00h
		XOR BL,BL
		SUB BL,3
		IDIV BL ; Divis. con segno di AX per r/m8: ris. in AL, resto in AH
		MOV Ris4,AX
	// --------------------------------------
		MOV AX,Mat
		OR EAX,0000FFF1h
		AND EAX,0000000Fh
		MOV BL,-251
		MUL BL ; Molt. senza segno di AL per r/m8: ris. in AX
		MOV Ris5,AX
	}

	printf("FL: %f\n", *(float*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}