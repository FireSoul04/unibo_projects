#include <stdio.h>

#ifdef _WIN32 /* valido sia per 32 che 64 bit */
	#define FFLUSH fflush(stdin)
#else
    void _fflush() {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    #define FFLUSH _fflush()
#endif

int main() {
    int int_var;
    float float_var;
    double double_var;
    char char_var;
    int int_array[5] = { 10, 20, 30, 40, 50 };

    int *ptr_int = &int_var;
    float *ptr_float = &float_var;
    double *ptr_double = &double_var;
    char *ptr_char = &char_var;
    int *ptr_array = int_array;

    printf("Inserisci un numero intero:");
    scanf("%d", &int_var);
    FFLUSH;

    printf("Inserisci un numero con la virgola (massimo 7 cifre dopo la virgola):");
    scanf("%f", &float_var);
    FFLUSH;
    
    printf("Inserisci un numero con la virgola (massimo 15 cifre dopo la virgola):");
    scanf("%lf", &double_var);
    FFLUSH;
    
    printf("Inserisci un carattere:");
    scanf("%c", &char_var);
    FFLUSH;

    printf("\n");
    printf("");

    return 0;
}