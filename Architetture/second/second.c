#include <stdio.h>

typedef unsigned int u32;
typedef unsigned short u16;

u32 moltiplica(u16 n1, u16 n2);
u32 uint_sqrt(u32 n);

int main() {
	printf("Prodotto=%u\n", moltiplica(0, 5));
	printf("Prodotto=%u\n", moltiplica(1, 5));
	printf("Prodotto=%u\n", moltiplica(4, 0));
	printf("Prodotto=%u\n", moltiplica(4, 1));
	printf("Prodotto=%u\n", moltiplica(4, 3));

	puts("");

	printf("Radice=%d\n", uint_sqrt(0));
	printf("Radice=%d\n", uint_sqrt(1));
	printf("Radice=%d\n", uint_sqrt(2));
	printf("Radice=%d\n", uint_sqrt(10));
	printf("Radice=%d\n", uint_sqrt(1089));

	return 0;
}

u32 moltiplica(u16 n1, u16 n2) {
	u32 prodotto;
	__asm {
		mov ax, n1
		cmp ax, n2
		jae noswap				; controllo se n2 è maggiore e lo scambio con n1 se vero
		xchg ax, n2
		mov n1, ax
	noswap:
		xor eax, eax			; azzero eax e lo utilizzo per il risultato del prodotto 
		xor ebx, ebx
		mov bx, n1				; salvo n1 in ebx come quantità da sommare
		mov cx, n2				; salvo n2 in ecx come contatore
	sum:
		cmp cx, 0				; controllo se il contatore è a 0
		je end
		add eax, ebx			; aggiungo al risultato n1
		dec cx
		jmp sum					; continuo il ciclo
	end:
		mov prodotto, eax		; salvo il risultato nella variabile prodotto
	}
	return prodotto;
}

u32 uint_sqrt(u32 n) {
	u32 res;
	__asm {
		xor eax, eax			; azzero eax e ci salvo il risultato
		mov ebx, n				; salvo in ebx il radicando
		mov ecx, 1				; salvo in ecx il numero s da togliere a n
	sqrt:
		sub ebx, ecx			; sottraggo s a n
		cmp ebx, 0
		jl end					; esce dal ciclo quando n arriva a un numero negativo o zero
		inc eax					; aumento risultato
		inc ecx					; aumento di due s
		inc ecx
		jmp sqrt
	end:
		mov res, eax			; salvo eax nel risultato
	}
	return res;
}