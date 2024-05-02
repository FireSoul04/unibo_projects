/********************************************************************************
 *                                                                              *
 *                   Architetture dei sistemi di Elaborazione                   *
 *                                                                              *
 ********************************************************************************

 Elaborato 1
 Descrizione: Dato un array di puntatori a stringa (ogni cella del vettore contiene
				l'indirizzo a 32 bit del primo carattere della stringa), ordinarlo
				secondo il codice ASCII. Ogni stringa termina con il carattere nullo
				(codice ASCII 0).

 ********************************************************************************/

#include <stdio.h>

void main() {
	// Le stringhe da ordinare (array di puntatori)
	char* strings[] = { "prova","1","adfadfas","bsfufdasi","ciao" };
	// Il numero di stringhe nell'array
	int num = sizeof(strings) / sizeof(strings[0]);

	// Stampa su video
	int i;
	for (i = 0; i < num; i++)
		printf("%s\n", strings[i]);
	puts("");

	int N;

	__asm {
		mov eax, 2
		mov ebx, 0
		call compara_stringa
		mov N, eax
		cmp eax, 0
		ja str_maggiore
	str_minore:
		mov eax, 2
		mov ebx, 0
		jmp scambia
	str_maggiore:
		mov eax, 0
		mov ebx, 2
	scambia:
		call scambia_stringa
		jmp fine

	compara_stringa: // Compara due stringhe negli indici eax e ebx
		lea edx, strings
		mov esi, [edx + eax * 4]
		mov edi, [edx + ebx * 4]
		xor ecx, ecx
	ciclo_compara:
		cmp [esi + ecx], 0 // Controllo se la prima stringa arriva alla fine
		je fine_compara
		cmp [edi + ecx], 0 // Controllo se la seconda stringa arriva alla fine
		je fine_compara
		inc ecx
		mov al, [esi + ecx]
		cmp al, [edi + ecx] // Se i caratteri sono uguali continuo il ciclo
		je ciclo_compara
		jb minore
	maggiore:
		mov eax, 1	// Se è maggiore ritorna 1
		jmp fine_compara
	minore:
		mov eax, -1	// Se è minore ritorna -1
	fine_compara:
		ret

	scambia_stringa: // Scambia le posizioni di due stringhe, prende i valori dei due indici in eax e ebx
		lea esi, strings
		mov edi, [esi + eax * 4]
		xchg edi, [esi + ebx * 4]
		mov [strings + eax * 4], edi
		ret

	fine:
	}

	printf("\nDifferenza str: %d\n\n", N);


	// Stampa su video
	for (i = 0; i < num; i++)
		printf("%s\n", strings[i]);
}
