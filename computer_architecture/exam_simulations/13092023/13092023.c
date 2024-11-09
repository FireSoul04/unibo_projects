#include <stdio.h>

int main() {
	unsigned int fl = 0x44444100;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX,Mat
		OR AX,0A0Bh
		ROR AX,4
		ADD AX,-9
		MOV Ris1,AX
	// --------------------------------------
		MOV AX,Mat
		AND AH,AL
		AND AH,5
		JNZ L1
		INC AH
		JMP L2
	L1: SUB AH,1
	L2: MOV Ris2,AX
	// --------------------------------------
		MOV AX,Mat
		MOV DL,AL
		NOT DL
		MOV ECX,99
	L3: MOV BYTE PTR Vet[ECX-1],DL
		LOOP L3
		AND DL,0Fh
		ADD DL,7
		XOR EBX,EBX
		MOV BL,DL
		MOV WORD PTR Vet[EBX],AX
		MOV ECX,95
	L4: CMP WORD PTR Vet[ECX],AX
		JE L5
		LOOP L4
	L5: MOV CH,CL
		NOT CL
		MOV Ris3,CX
	// --------------------------------------
		MOV AX,Mat
		AND AL,70h
		OR AL,80h
		XOR BL,BL
		SUB BL,2
		IMUL BL ; Moltiplic. con segno di AL per r/m8: ris. in AX
		MOV Ris4,AX
	// --------------------------------------
		MOV AX,Mat
		OR AX,0FF01h
		MOV BL,-2
		IDIV BL ; Divis. con segno di AX per r/m8: ris. in AL, resto in AH
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