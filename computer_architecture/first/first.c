#include <stdio.h>

int main() {
	// Esercizio 1
	__asm {
		mov eax, 3
		mov ebx, eax
		add eax, 2
		add ebx, eax
		and eax, ebx
		and ebx, 9
		inc eax
		dec ebx
	}

	// Esercizio 2
	__asm {
		mov eax, 2
		mov ebx, 3
		jmp etic
		mov eax, 5
	etic:
		mov edx, 7
	}

	// Esercizio 3
	__asm {
		mov eax, 3
	e1:
		cmp eax, 5
		jg fine
		inc eax
		jmp e1
	fine:
		sub eax, 5
	}

	// Esercizio 4
	__asm {
	;part 1
		mov ebx, 1
		mov eax, 10
	l1:
		add ebx, 2
		dec eax
		jnz l1

	;part 2
		mov ecx, 2
		mov eax, 1
	ciclo1:
		cmp ecx, 10
		jg fine1
		mul ecx
		inc ecx
		jmp ciclo1
	fine1:
		mov edx, eax

	;part 3
		mov ebx, 10
		mov eax, 0
	c1:
		cmp ebx, eax
		je fine2
		inc eax
		dec ebx
		jmp c1
	fine2:
		
	;part 4
		mov ecx, 1
		mov eax, 0
	ciclo2:
		cmp ecx, 10
		jge fine3
		add eax, ecx
		inc ecx
		jmp ciclo2
	fine3:
		mov edx, eax
	}

	// Esercizio 5
	__asm {
		mov ecx, 10
		xor eax, eax
	label:
		add eax, ecx
		loop label
	}

	return 0;
}