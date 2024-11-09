#include <stdio.h>

void main() {
	// Le stringhe da ordinare (array di puntatori)
	char* strings[] = { "prova","1","adfadfas","bsfufdasi","ciao" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);

	__asm
	{
		MOV EDX, 0

		ciclo:
		CMP EDX, num
		JAE fine
		MOV EBX, 0

		ciclo_2:
		CMP EBX, num
		JAE nuova_cella
		MOV EAX, 0
		MOV ESI, strings[EDX * 4]
		MOV EDI, strings[EBX * 4]
		CMP EBX, EDX
		JE nuova_parola

		ciclo_3:
		MOV CL, [ESI + EAX]
		MOV CH, [EDI + EAX]
		CMP CL, CH
		JL inverti
		JA nuova_parola
		INC EAX
		CMP CL, 0
		JE nuova_parola
		JMP ciclo_3

		inverti:
		MOV strings[EBX * 4], ESI
		MOV strings[EDX * 4], EDI
		INC EBX
		JMP ciclo_2

		nuova_cella:
		INC EDX
		JMP ciclo

		nuova_parola:
		INC EBX
		JMP ciclo_2

		fine:
	}

	// Stampa su video
	{
		int i;
		for (i = 0; i < num; i++)
			printf("%s\n", strings[i]);
	}
}