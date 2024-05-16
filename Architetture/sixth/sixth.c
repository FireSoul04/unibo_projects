#include <stdio.h>

int main() {
	int Vettore[] = { 3, 7, 3, 7, 5, 1, 4, -3, -7, -9, 2, 6 };
	unsigned int Lung = sizeof(Vettore) / sizeof(Vettore[0]);

	__asm {
		lea esi, Vettore
		mov ecx, Lung					// Salvo in ECX il primo contatore
	l1:
		mov eax, [esi + ecx * 4 - 4]	// Salvo in EAX il max
		mov edx, ecx					// Salvo in EDX la posizione del max
		mov ebx, ecx					// Salvo in EBX il secondo contatore
	l2:
		dec ebx
		cmp ebx, -1						// Controllo se il secondo contatore ha finito di scorrere il vettore
		je new_value
		mov edi, [esi + ebx * 4 - 4]	// Salvo in EDI il valore in posizione EBX
		cmp eax, edi					// Controllo se il valore del secondo contatore è più grande di max
		jg l2							// Se non è max rincomincio il ciclo
		mov eax, edi					// Salvo il nuovo max
		mov edx, ebx					// Salvo la posizione del nuovo max
		jmp l2							// Dopo aver settato il nuovo max torno all'inizio del ciclo
	new_value:
		mov edi, [esi + ecx * 4 - 4]	// Salvo temporaneamente in EDI il nuovo max
		mov [esi + ecx * 4 - 4], eax
		mov [esi + edx * 4 - 4], edi	// Scambio il nuovo max con il vecchio max
		loop l1
	}

	unsigned int i;
	for (i = 0; i < Lung; i++) {
		printf("Vettore[%2d] = %d\n", i, Vettore[i]);
	}

	return 0;
}