#include <stdio.h>

int main() {
	unsigned short int Mat = 4441;
	unsigned char Vet[100];
	unsigned short Ris1, Ris2, Ris3, Ris4, Ris5;

	__asm {
		MOV AX, Mat
		NOT AX
		XOR AL, 3Bh
		MOV BL, AH
		SHL BL, 3
		XOR BH, BH
		ADD AX, BX
		MOV Ris1, AX
	// --------------------------------------
		LEA ESI, Vet
		MOV AX, Mat
		MOV ECX, 16
	L1: MOV BL, AL
		AND BL, 3
		MOV BYTE PTR Vet[ECX], BL
		SHR AX, 2
		LOOP L1
		MOV AX, WORD PTR Vet[14]
		MOV DX, WORD PTR Vet[12]
		SHL DX, 4
		OR AX, DX
		MOV Ris2, AX
	// --------------------------------------
		XOR AX, AX
		MOV DX, Mat
		INC DX
		SUB AX, DX
		JS L2
		MOV AX, 0FFFFh
		JMP L3
	L2: NEG AX
		XCHG AL, AH				; XCHG a, b scambia il contenuto dei registri a e b
		ROL AX, 8
		ROL AL, 1
	L3: MOV Ris3, AX
	// --------------------------------------
		MOV AX, Mat
		AND AL, 70h
		OR AL, 80h
		XOR BL, BL
		SUB BL, 3
		IMUL BL					; Moltiplic. con segno di AL per r/m8: ris. in AX
		MOV Ris4, AX
	// --------------------------------------
		MOV AX, Mat
		XOR AH, AH
		XOR BL, BL
		ADD BL, 4
		DIV BL					; Divis.senza segno di AX per r/m8: risultato in AL, resto in AH
		MOV Ris5, AX
	}

	printf("Ris1: %hx, %hd\n", Ris1, Ris1);
	printf("Ris2: %hx, %hd\n", Ris2, Ris2);
	printf("Ris3: %hx, %hd\n", Ris3, Ris3);
	printf("Ris4: %hx, %hd\n", Ris4, Ris4);
	printf("Ris5: %hx, %hd\n", Ris5, Ris5);

	return 0;
}