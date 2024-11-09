#include <stdio.h>

int main() {
	unsigned int fl = 0xc4441400;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		OR EAX, 0000FFF1h
		MOV BL, -2
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		PUSH AX
		POP Ris1
		// --------------------------------------
		MOV AX, Mat
		XCHG AL, AH; scambia il contenuto dei due registri
		MOV WORD PTR Vet[8], AX
		ROR BYTE PTR Vet[9], 4
		PUSH WORD PTR Vet[8]
		POP Ris2
		// --------------------------------------
		MOV ECX, 15
		XOR EAX, EAX
		L1 : ADD EAX, ECX
		MOV Vet[ECX], CL
		LOOP L1
		MOV CX, 00F1h
		OR CX, Mat
		AND CX, 000Fh
		MOV AH, Vet[ECX]
		MOV Ris3, AX
		// --------------------------------------
		MOV AX, Mat
		AND AH, AL
		AND AH, 0110b
		JNZ L2
		INC AH
		JMP L3
		L2 : SUB AH, 3
		L3 : MOV Ris4, AX
		// --------------------------------------
		MOV AX, Mat
		OR EAX, 0000FFF1h
		AND EAX, 0000000Fh
		MOV BL, -1
		SUB BL, 250
		MUL BL; Molt.senza segno di AL per r / m8: ris.in AX
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