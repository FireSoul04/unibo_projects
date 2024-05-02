#include <stdio.h>

int main() {
	int Vettore[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, -1, -2, -3 };
	unsigned int Lung = sizeof(Vettore) / sizeof(int);
	int Somma;
	int Media;

	__asm {
		xor eax, eax //Somma
		mov ecx, Lung
		lea ebx, Vettore
	somma:
		add eax, dword ptr [ebx + ecx * 4 - 4]
		loop somma
	media:
		mov Somma, eax
		cdq
		idiv Lung
		mov Media, eax
	}

	printf("Somma=%d\n", Somma);
	printf("Media=%d\n", Media);

	return 0;
}