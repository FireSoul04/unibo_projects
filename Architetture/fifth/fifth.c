#include <stdio.h>

int main() {
	unsigned char Vettore[] = { 3, 7, 3, 7, 5 };
	unsigned int Lung = sizeof(Vettore) / sizeof(Vettore[0]);
	int Ris;

	__asm {
		xor eax, eax // Valore dove salvo la somma
		lea esi, Vettore
	loop_mask:
		mov bl, [esi + ecx - 1]			// Prendo un byte del vettore e lo salvo in ebx
	check_bits:
		cmp bl, 0
		je repeat
		test bl, 1						// Controllo se il primo bit è 1
		je shift_bits
		xor eax, 1						// Gestisco la somma con un xor in modo da non gestire la carry
	shift_bits:
		shr bl, 1						// Eseguo uno shift di un bit finché non sono tutti zeri
		jmp check_bits
	repeat:
		loop loop_mask
	end:
		mov Ris, eax
	}

	printf("Ris=%d", Ris);

	return 0;
}