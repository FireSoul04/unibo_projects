#include <stdio.h>
#include <math.h>

// FORMATTAZIONE DI PRINTF DI DAVIDE
// printf("<operazione><variabile> = <valore nuovo>");
// printf("<operazione><variabile> = <assegnazione> => <variabile> = <valore nuovo>");

int main() {
    char charOutOfBounds = 27452;
    int n1Integer = 7, n2Integer = 5, n3Integer = 4, intOutOfBounds = 4.3e+23, result;
    float n1Float = 3.4f, n2Float = 4.74f, floatOutOfBounds = 5.2e+251, resultf;
    double n1Double = -13.2, n2Double = 0.523;

    printf("char = %c (dovrebbe essere 27452)\n", charOutOfBounds);
    printf("int = %d (dovrebbe essere 4.3e+23)\n", intOutOfBounds);
    printf("float = %f (dovrebbe essere 5.2e+251)\n", floatOutOfBounds);

    n1Float = n1Integer / n2Integer;
    printf("n1Float = n1Integer / n2Integer => n1Float = %f\n", n1Float);
    n1Float = (float)n1Integer / n2Integer;
    printf("n1Float = (float)n1Integer / n2Integer => n1Float =  %f\n", n1Float);
    n1Float = n1Integer / 3.0;
    printf("n1Float = n1Integer / 3.0 => n1Float =  %f\n", n1Float);

    printf("n1Integer = %d, n2Integer = %d\n", n1Integer, n2Integer);
    // Cambia il segno
    printf("+n1Integer = %+d, -n2Integer = %+d\n\n", +n1Integer, -n2Integer);

    // Operatori compatti
    // Salva subito il valore
    printf("++n1Integer = %d, --n2Integer = %d, n1Integer = %d, n2Integer = %d\n", ++n1Integer, --n2Integer, n1Integer, n2Integer);
    // Salva il valore dopo l'utilizzo
    printf("n1Integer++ = %d, n2Integer-- = %d, n1Integer = %d, n2Integer = %d\n", n1Integer++, n2Integer--, n1Integer, n2Integer);

    printf("Side effects (non sai quale operatore ha la precedenza):\n");
    printf("n1Integer = %d, n2Integer = %d\n\n", n1Integer, n2Integer);
    n1Integer = ++n2Integer;
    printf("n1Integer = ++n2Integer => n1Integer = %d\n", n1Integer);
    n1Integer = n2Integer--;
    printf("n1Integer = n2Integer-- => n1Integer = %d\n", n1Integer);
    n1Integer = n3Integer + n2Integer++;
    printf("n1Integer = n3Integer + n2Integer++ => n1Integer = %d\n", n1Integer);
    n1Integer = n2Integer * n2Integer++;
    printf("n1Integer = n2Integer * n2Integer++ => n1Integer = %d\n", n1Integer);
    printf("n1Integer = %d, n2Integer = %d\n\n", n1Integer, n2Integer);

    // Assegnazione
    n1Integer = 7;
    n2Integer = 5;
    printf("n1Integer = %d, n2Integer = %d\n", n1Integer, n2Integer);
    printf("n1Float = %f, n2Float = %f\n\n", n1Float, n2Float);
    // Operatori aritmetici
    result = n1Integer + n2Integer;
    printf("n1Integer + n2Integer = %d\n", result);

    result = n1Integer - n2Integer;
    printf("n1Integer - n2Integer = %d\n", result);

    result = n1Integer * n2Integer;
    printf("n1Integer * n2Integer = %d\n", result);

    if (n2Integer != 0) {
        result = n1Integer / n2Integer;
        resultf = n1Float / n2Float;
        printf("n1Integer / n2Integer = %d\n", result);
        printf("n1Float / n2Float = %f\n", resultf);
    } else {
        printf("Usare un numero diverso da 0 nella divisione\n");
    }

    if (n2Integer != 0) { 
        result = n1Integer % n2Integer; // Se sono entrambi interi, caso contrario non compilerà, es. n1Float % n2Integer
        printf("n1Integer %% n2Integer = %d\n\n", result);
    } else {
        printf("Usare un numero diverso da 0 nell'operazione modulo\n\n");
    }

    // Operatori aritmetici con assegnazione
    n1Integer += n2Integer;
    printf("n1Integer += n2Integer => n1Integer = %d\n", n1Integer);

    n1Integer -= n2Integer;
    printf("n1Integer -= n2Integer => n1Integer = %d\n", n1Integer);

    n1Integer *= n2Integer;
    printf("n1Integer *= n2Integer => n1Integer = %d\n", n1Integer);

    if (n2Integer != 0) {
        n1Integer /= n2Integer;
        printf("n1Integer /= n2Integer => n1Integer = %d\n", n1Integer);
    } else {
        printf("Usare un numero diverso da 0 nella divisione\n");
    }
    if (n2Integer != 0) { 
        n1Integer %= n2Integer; // Se sono entrambi interi, caso contrario non compilerà, es. n1Float % n2Integer
        printf("n1Integer %%= n2Integer => n1Integer = %d\n\n", n1Integer);
    } else {
        printf("Usare un numero diverso da 0 nell'operazione modulo\n\n");
    }

    printf("size of n1Integer = %d bytes\n", sizeof(n1Integer));
    printf("size of n1Float = %d bytes\n", sizeof(n1Float));
    
    printf("cast n2Float to int = %d\n", (int)n2Float);
    printf("cast n2Integer to float = %f\n\n", (float)n2Integer);

    printf("Valori che vanno oltre il massimo possibile per il tipo di variabile:\n");

    printf("Funzioni math.h:\n");
    printf("Funzioni cos(n1Float) = %f\n", cos(n1Double));
    printf("Funzioni sin(n1Float) = %f\n", sin(n1Double));
    printf("Funzioni sin(n1Float) = %f\n", sinh(n1Double));
    printf("Funzioni cos(n1Float) = %f\n", cosh(n1Double));
    printf("Funzioni asin(n2Float) = %f\n", asin(n2Double));
    printf("Funzioni acos(n2Float) = %f\n", acos(n2Double));
    printf("Funzioni tan(n1Float) = %f\n", tan(n1Double));
    printf("Funzioni tanh(n1Float) = %f\n", tanh(n1Double));
    printf("Funzioni atan(n1Float) = %f\n", atan(n1Double));
    printf("Funzioni atan2(n1Float, n2Float) = %f\n", atan2(n1Double, n2Float));
    printf("Funzioni exp(n1Float) = %f\n", exp(n1Double));
    printf("Funzioni frexp(n1Float, &n1Integer) = %f, n1Integer = %d\n", frexp(n1Double, &n1Integer), n1Integer);
    printf("Funzioni ldexp(n1Float, n1Integer) = %f\n", ldexp(n1Double, n1Integer));
    printf("Funzioni log(n1Float) = %f\n", log(n1Double));
    printf("Funzioni log10(n1Float) = %f\n", log10(n1Double));
    printf("Funzioni log2(n1Float) = %f\n", log2(n1Double));
    printf("Funzioni modf(n1Float, n1Integer) = %f, n1Integer = %f\n", modf(n1Double, &n2Double), n2Double);
    printf("Funzioni pow(n1Float, n2Float) = %f\n", pow(n1Double, n2Double));
    printf("Funzioni sqrt(n1Float) = %f\n", sqrt(n1Double));
    printf("Funzioni ceil(n1Float) = %f\n", ceil(n1Double));
    printf("Funzioni floor(n1Float) = %f\n", floor(n1Double));
    printf("Funzioni fabs(n1Float) = %f\n", fabs(n1Double));
    printf("Funzioni fmod(n1Float, n2Float) = %f\n", fmod(n1Double, n2Double));

    return 0;
}