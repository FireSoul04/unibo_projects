#include <stdio.h>

int main() {
	float fl = -7441.875;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV DX, Mat
		MOV AX, DX
		OR AX, 0FEFDh
		XOR DX, AX
		NEG DX
		MOV Ris1, DX
		// --------------------------------------
		MOV DX, Mat
		LEA ESI, Vet
		ADD ESI, 10h
		MOV ECX, 4
		L1: MOV[ESI + ECX * 2], DX
		LOOP L1
		LEA ESI, Vet
		ADD ESI, 17h
		MOV AX, [ESI]
		ROL AX, 3
		MOV Ris2, AX
		// --------------------------------------
		XOR ECX, ECX
		MOV CX, Mat
		AND CX, 111b
		OR CX, 10b
		MOV AX, Mat
		L2 : MOV WORD PTR Vet[15 + ECX * 4], AX
		MOV WORD PTR Vet[13 + ECX * 4], AX
		LOOP L2
		MOV CX, Mat
		XOR CX, WORD PTR Vet[18]
		MOV Ris3, CX
		// --------------------------------------
		MOV AX, Mat
		AND AL, 70h
		OR AL, 8Fh
		XOR BL, BL
		SUB BL, 9
		IMUL BL; Moltiplic.con segno di AL per r / m8: ris.in AX
		MOV Ris4, AX
		// --------------------------------------
		PUSH Mat
		MOV EAX, 1
		DEC EAX
		POP AX
		OR AX, 0FF00h
		XOR BL, BL
		ADD BL, 9
		IDIV BL; Divis.con segno di AX per r / m8: ris.in AL, resto in AH
		MOV Ris5, AX
	}

	printf("FL: %x\n", *(unsigned int*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}