#include <stdio.h>

int main() {
	float fl = -64441.8125;
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV CX,Mat
		MOV BX,CX
		XOR CX,00F0Fh
		XOR CX,0F0F0h
		NOT CX
		OR CX,2
		AND CX,0Fh
		ROL BX,CL
		MOV Ris1,BX
	// --------------------------------------
		MOV AX,Mat
		AND AL,00010000b
		JZ L1
		OR AH,01101010b
		JMP L2
	L1: XOR AH,01010100b
	L2: MOV Ris2,AX
	// --------------------------------------
		MOV AX,Mat
		MOV BYTE PTR Vet[10],AL
		MOV BYTE PTR Vet[14],99
		MOV BYTE PTR Vet[18],AH
		MOV BYTE PTR Vet[22],17
		LEA ESI,Vet
		ADD ESI,9
		XOR EBX,EBX
		MOV ECX,4
	L3: XOR BL,[ESI+1]
		ADD ESI,4
		LOOP L3
		MOV Ris3,BX
	// --------------------------------------
		MOV AX,Mat
		AND AL,73h
		OR AL,90h
		XOR BL,BL
		SUB BL,2
		IMUL BL ; Moltiplic. con segno di AL per r/m8: ris. in AX
		MOV Ris4,AX
	// --------------------------------------
		MOV AX,Mat
		XOR AH,AH
		XOR BL,BL
		ADD BL,5
		DIV BL ; Divis. senza segno di AX per r/m8: risultato in AL, resto in AH
		MOV Ris5,AX
	}

	printf("FL: %x\n", *(unsigned int*)&fl);
	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);


	return 0;
}