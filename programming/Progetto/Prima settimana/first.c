#include <stdio.h>

/*
    GRUPPO FORMATO DA:

    TAZZIERI NICOLAS -
    STRIMBEI ALEXANDRA -
    MANCINI DAVIDE -
    BERTOISE ODILE -
*/


//FORMATTAZIONE STAMPA VARIABILI: printf("<tipo> contiene: <var>. Occupa <byte> byte")

int main()
{
    //Variabile in cui assegno il numero restutuito dalla funzione printf per il conteggio dei caratteri
    int charPrinted = 0;

    //dichiarazione delle variabili primitive
    int integer, maxInteger, minInteger;
    char character, maxCharacter, minCharacter;
    float metersF, maxFloat, minFloat;
    double metersD, maxDouble, minDouble;

    short int shortInteger, maxShortInteger, minShortInteger;
    long int longInteger, maxLongInteger, minLongInteger;
    long double metersLd, maxLongDouble, minLongDouble;
    long long int longLongInteger, maxLongLongInteger, minLongLongInteger;

    unsigned int unsignedInteger, maxUnsignedInteger, minUnsignedInteger;
    unsigned short int unsignedShortInteger, maxUnsignedShortInteger, minUnsignedShortInteger;
    unsigned long int unsignedLong, maxUnsignedLongInteger, minUnsignedLongInteger;
    unsigned long long int unsignedLongLongInteger, maxUnsignedLongLongInteger, minUnsignedLongLongInteger;
    unsigned char unsignedCharacter, maxUnsignedCharacter, minUnsignedCharacter;

    //

    //Assegno variabili primitive
    integer = 230;
    shortInteger = 25;
    longInteger = 123;
    character = 'c';

    // Assegno dei numeri con una precisione massima che può permettere in base alla tipologia
    metersF = 5.026644;
    metersD = 7.02143237543;

    metersLd = 3.210290L;
    longLongInteger = 23732864L;

    //assegnazione unsigned int e char
    unsignedInteger = 124374;
    unsignedShortInteger = 14245;
    unsignedLong = 8364743;
    unsignedLongLongInteger = 18273659;
    unsignedCharacter = 184; //Lo assegno come int per far capire che prendo un valore della tab. ascii estesa

    //
    maxInteger = 0x7fffffff;
    minInteger = 0x80000000;

    maxShortInteger = 0x7fff;
    minShortInteger = 0x8000;

    maxCharacter = 0x7f;
    minCharacter = 0x80;

    maxLongInteger = 0x7fffffff;
    minLongInteger = 0x80000000;

    maxLongLongInteger = 0x7fffffffffffffffL;
    minLongLongInteger = 0x8000000000000000L;

    //Assegno il massimo e minimo in forma esadecimale per tutti i valori unsigned
    maxUnsignedInteger = 0xffffffff;
    minUnsignedInteger = 0x0;

    maxUnsignedShortInteger = 0xffff; //2byte
    minUnsignedShortInteger = 0x0;

    maxUnsignedLongInteger = 0xffffffff; //4 byte
    minUnsignedLongInteger = 0x0;

    maxUnsignedLongLongInteger = 0xffffffffffffffffL; //8byte
    minUnsignedLongLongInteger = 0x0L;

    maxUnsignedCharacter = 0xff; //1byte
    minUnsignedCharacter = 0x0;

    // Assegno il massimo e minimo delle tipologie floating point in forma esponenziale
    // Massimo e minimo dei float e double
    maxFloat = 3.4e+38;
    minFloat = 1.2e-38;

    minDouble = 2.3e-308;
    maxDouble = 1.7e+308;

    // Massimo e minimo dei long double e richiede di aggiungere una L alla fine per indicare che è un long double
    maxLongDouble = 1.1e+4932L;
    minLongDouble = 3.4e-4932L;

    /*
        Stampo per ogni tipologia la variabile, quanti byte occupa una certa tipologia
        e quanto è il limite minimo e massimo di valori di una certa tipologia
    */
    //Stampo anche il segno
    charPrinted = printf("integer (int) contiene: %+d. Occupa %lu byte. Max: %d. Min: %d\n",
                         integer, sizeof(integer), maxInteger, minInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("character (char) contiene: %c. Occupa %lu byte. Max: %hhd. Min: %hhd\n",
                         character, sizeof(character), maxCharacter, minCharacter);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("shortInteger (short int) contiene: %hd. Occupa %lu byte. Max: %hd. Min: %hd\n",
                         shortInteger, sizeof(shortInteger), maxShortInteger, minShortInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("longInteger (long int) contiene: %ld. Occupa %lu byte. Max: %ld. Min: %ld\n",
                         longInteger, sizeof(longInteger), maxLongInteger, minLongInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("longLongInteger (long long int) contiene: %lld. Occupa %lu byte. Max: %lld. Min: %lld\n",
                         longLongInteger, sizeof(longLongInteger), maxLongLongInteger, minLongLongInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("metersF (float) contiene (approssimato a 3 decimali): %.3f. Occupa %lu byte. Max: %.1e. Min: %.1e\n",
                         metersF, sizeof(metersF), maxFloat, minFloat);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("metersD (double) contiene (approssimato a 6 decimali): %.6f. Occupa %lu byte. Max: %.1e. Min: %.1e\n",
                         metersD, sizeof(metersD), maxDouble, minDouble);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("metersLd (long double) contiene (approssimato a 12 decimali): %.12Lf. Occupa %lu byte. Max: %.1Le. Min: %.1Le\n",
                         metersLd, sizeof(metersLd), maxLongDouble, minLongDouble);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("unsignedInteger (unsigned int) contiene: %u. Occupa %lu byte. Max: %u. Min: %u\n",
                         unsignedInteger, sizeof(unsignedInteger), maxUnsignedInteger, minUnsignedInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("unsignedShortInteger (unsigned short int) contiene: %hu. Occupa %lu byte. Max: %hu. Min: %hu\n",
                         unsignedShortInteger, sizeof(unsignedShortInteger), maxUnsignedShortInteger, minUnsignedShortInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("unsignedLong (unsigned long int) contiene: %lu. Occupa %lu byte. Max: %lu. Min: %lu\n",
                         unsignedLong, sizeof(unsignedLong), maxUnsignedLongInteger, minUnsignedLongInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("unsignedLongLongInteger (unsigned long long int) contiene: %llu. Occupa %lu byte. Max: %llu. Min: %llu\n",
                         unsignedLongLongInteger, sizeof(unsignedLongLongInteger), maxUnsignedLongLongInteger, minUnsignedLongLongInteger);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("unsignedChar (char) contiene: %c. Occupa %lu byte. Max: %hhu. Min: %hhu\n",
                         unsignedCharacter, sizeof(unsignedCharacter), maxUnsignedCharacter, minUnsignedCharacter);
    printf("Caratteri stampati: %d\n", charPrinted);

    printf("\n\n");

    //Utilizzo il resto dei caratteri di conversione
    charPrinted = printf("Il campo minimo minimo e' 20: %20d| stampo a destra\n", integer);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("Il campo minimo minimo e' 20: %-20d| stampo a sinistra\n", integer);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("Il campo minimo minimo e' 20: %020d| stampo a destra e rimpiazzo gli spazi con degli 0\n", integer);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("Aggiungo uno spazio in piu' prima di % d\n", integer);
    printf("Caratteri stampati: %d\n", charPrinted);

    //Stampo in ottale e esadecimale in entrambi i formati
    charPrinted = printf("%d in ottale e' %o oppure %#o\n", integer, integer, integer);
    printf("Caratteri stampati: %d\n", charPrinted);

    charPrinted = printf("%d in esadecimale e' %x oppure %#x\n", integer, integer, integer);
    printf("Caratteri stampati: %d\n", charPrinted);


    /*charPrinted = printf("Float variable (6 digits precision): %.6f, Size: %u bytes, Max: %.1e, Min: %.1e \n",
                        metersF, sizeof(metersF), maxFloat, minFloat);
    printf("Caratteri stampati: %d\n", charPrinted);
    charPrinted = printf("Double variable (15 digits precision): %.15lf, Size: %u bytes, Max: %.1e, Min: %.1e \n",
                        metersD, sizeof(metersD), maxDouble, minDouble);
    printf("Caratteri stampati: %d\n", charPrinted);
    charPrinted = printf("Long double variable (19 digits precision): %.19Lf, Size: %u bytes, Max: %.1Le, Min: %.1Le \n",
                        metersLd, sizeof(metersLd), maxLongDouble, minLongDouble);*/
    return 0;
}
