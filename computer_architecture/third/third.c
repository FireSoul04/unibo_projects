#include <stdio.h>

int find_first_occurrency(char Carattere);
int is_num_a_power_of_2(unsigned int Num);

char Stringa[] = "Questa è una stringa!";
int Lunghezza = sizeof(Stringa) - 1;

int main() {
	// Trova prima occorrenza in una stringa
	printf("Stringa=%s\n", Stringa);
	printf("Carattere=%c, Posizione=%d\n", Stringa[0], find_first_occurrency(Stringa[0]));
	printf("Carattere=%c, Posizione=%d\n", Stringa[Lunghezza - 1], find_first_occurrency(Stringa[Lunghezza - 1]));
	printf("Carattere=%c, Posizione=%d\n", Stringa[Lunghezza / 2], find_first_occurrency(Stringa[Lunghezza / 2]));
	printf("Carattere=%c, Posizione=%d\n", 'ì', find_first_occurrency('ì'));

	// Controllare se un numero è potenza di 2
	printf("Num=%d Ris=%d\n", 0, is_num_a_power_of_2(0));
	printf("Num=%d Ris=%d\n", 1, is_num_a_power_of_2(1));
	printf("Num=%d Ris=%d\n", 2, is_num_a_power_of_2(2));
	printf("Num=%d Ris=%d\n", 3, is_num_a_power_of_2(3));
	printf("Num=%d Ris=%d\n", 65536, is_num_a_power_of_2(65536));
	printf("Num=%d Ris=%d\n", 65537, is_num_a_power_of_2(65537));
	find_first_occurrency_str('Q');

	return 0;
}

int find_first_occurrency(char Carattere) {
	int Posizione;

	__asm {
		xor ecx, ecx
		mov bl, Carattere
		lea esi, Stringa
	search_loop:
		mov al, [esi + ecx];
		inc ecx
		cmp al, bl
		je end
		cmp ecx, Lunghezza
		jb search_loop
		jne end
		xor ecx, ecx
	end:
		dec ecx // Ecx = -1
		mov Posizione, ecx
	}

	return Posizione;
}

int is_num_a_power_of_2(unsigned int Num) {
	unsigned int Ris = 0;

	__asm {
		xor ebx, ebx
		inc ebx
		mov eax, Num
		cmp eax, 0
		je end
	check_power_of_2:
		test eax, ebx // Confronta con 1
		jnz check_other_bits
		shr eax, 1
		jmp check_power_of_2
	check_other_bits:
		cmp eax, ebx
		jne end
		inc Ris
	end:
	}

	return Ris;
}