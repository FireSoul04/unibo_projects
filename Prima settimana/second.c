#include <stdio.h>

/*
    GRUPPO FORMATO DA:

    TAZZIERI NICOLAS - nicolas.tazzieri@studio.unibo.it
    STRIMBEI ALEXANDRA - strimberi.alexandra@studio.unibo.it
    MANCINI DAVIDE - davide.mancini10@studio.unibo.it
    BERTOISE ODILE - tchakoute.odile@studio.unibo.it
*/

//Definisco il fattore di conversione da miglia per gallone a litri per 100km
#define MILES_TO_KILOMETERS (1.60934)
#define GALLONS_TO_LITERS (3.78541)

int main()
{
    //inizializzazione variabili input
    float miles = 0;
    float gallons = 0;

    //Input dei dati
    printf("Inserisci il numero di miglia percorse: ");
    scanf("%f", &miles);
    fflush(stdin);
    printf("Inserisci il numero di galloni di benzina consumati: ");
    scanf("%f", &gallons);
    fflush(stdin);

    //Ottengo le miglia per gallone (uso un double in quanto ha una precisione doppia)
    double milesPerGallon = miles / gallons;

    //Effettuo le conversioni
    float kilometers = miles * MILES_TO_KILOMETERS;
    float liters = gallons * GALLONS_TO_LITERS;

    double litersPerHundredKilometers = liters / (100 * kilometers);

    printf("\n\n");
    //Output
    printf("Miglia per gallone effettuate: %.2lf\n", milesPerGallon);
    printf("Litri per 100km consumati: %.3lf\n", litersPerHundredKilometers);


    return 0;
}
