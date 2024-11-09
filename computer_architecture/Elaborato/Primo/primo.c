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

	__asm {
	// Ordina l'array strings in base ai valori della tabella ASCII
		xor eax, eax						// Contatore della prima stringa
	ciclo_prima_stringa:
		cmp eax, num						// Esco da entrambi i cicli se il primo contatore arriva alla fine dell'array
		je fine
		xor ebx, ebx						// Contatore della seconda stringa
	ciclo_seconda_stringa:
		cmp ebx, num						// Esco dal secondo ciclo e aggiorno il contatore del primo ciclo
		je incrementa_primo_contatore
		cmp eax, ebx						// Caso particolare in cui gli indici sono uguali
		je incrementa_secondo_contatore
		call compara_stringa
		cmp edx, 0							// Controllo il risultato del confronto tra stringhe
		jle incrementa_secondo_contatore
		call scambia_stringa				// Se la prima stringa è minore della seconda scambia i puntatori
	incrementa_secondo_contatore:
		inc ebx
		jmp ciclo_seconda_stringa
	incrementa_primo_contatore:
		inc eax
		jmp ciclo_prima_stringa

	// Compara due stringhe di strings negli indici eax e ebx seguendo i valori della tabella ASCII
	// ritorna in edx 0 se è uguale, 1 se è maggiore o -1 se è minore
	compara_stringa:
		mov esi, [strings + eax * 4]
		mov edi, [strings + ebx * 4]
		xor ecx, ecx
	ciclo_compara:
		mov dl, [esi + ecx]			// Salvo ogni carattere delle stringhe
		mov dh, [edi + ecx]
		inc ecx
		cmp dl, 0					// Controllo se la prima stringa arriva alla fine
		je stringa_maggiore
		cmp dh, 0					// Controllo se la seconda stringa arriva alla fine
		je stringa_minore
		cmp dh, dl					// Se i caratteri sono uguali continuo il ciclo
		je ciclo_compara
		jl stringa_minore
	stringa_maggiore:
		mov edx, 1
		jmp fine_compara
	stringa_minore:
		mov edx, -1
		jmp fine_compara
	stringa_uguale:
		xor edx, edx				// Le due stringhe sono uguali e ritorno 0
	fine_compara:
		ret

	// Scambia le posizioni di due stringhe, prende i valori dei due indici in eax e ebx
	scambia_stringa:
		lea esi, strings
		mov edi, [esi + eax * 4]
		xchg edi, [esi + ebx * 4]
		mov [esi + eax * 4], edi
		ret

	fine:
	}


	// Stampa su video
	for (i = 0; i < num; i++)
		printf("%s\n", strings[i]);
}
