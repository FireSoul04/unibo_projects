/*
    GRUPPO FORMATO DA:

    TAZZIERI NICOLAS - nicolas.tazzieri@studio.unibo.it
    STRIMBEI ALEXANDRA - strimberi.alexandra@studio.unibo.it
    MANCINI DAVIDE - davide.mancini10@studio.unibo.it
    BERTOISE ODILE - tchakoute.odile@studio.unibo.it
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DEBUG_LOAN_INDEX 8      //Indice del loan da utilizzare come debug
#define LITTLE_STR 30
#define N_TRAINING_LOANS 7178   //circa 75% dei prestiti
#define N_TESTING_LOANS 2400    //circa 25% dei prestiti
#define MAX_LOANS 9579
#define K_VALUE 7               //Valore di k


#define CLEAR printf("\e[1;1H\e[2J");

//#define DEBUG 1

// Creo la mia struttura loan, contenente i dati dei prestiti
typedef struct Loan
{
    int credit_policy;           // 1 se il cliente soddisfa i criteri di sottoscrizione del credito; 0 altrimenti.
    float int_rate;               // Il tasso di interesse del prestito (ai mutuatari più rischiosi vengono assegnati tassi di interesse più elevati).
    char purpose[LITTLE_STR + 1]; // Lo scopo del prestito.
    float installment;            // Le rate mensili dovute dal mutuatario se il prestito viene finanziato
    float log_annual_inc;         // Il log naturale del reddito annuo autodichiarato del mutuatario.
    float dti;                    // Il rapporto debito/reddito del mutuatario (importo del debito diviso per il reddito annuale).
    int fico;                     // Il punteggio di credito FICO del mutuatario.
    float days_with_cr_line;      // Il numero di giorni in cui il debitore ha avuto una linea di credito.
    int revol_bal;                // Il saldo revolving del debitore (importo non pagato alla fine del ciclo di fatturazione della carta di credito).
    float revol_util;             // Il tasso di utilizzo della linea revolving del debitore (l'importo della linea di credito utilizzata rispetto al credito totale disponibile).
    int inq_last_6mths;           // Il numero di richieste di informazioni da parte dei creditori negli ultimi 6 mesi
    int delinq_2yrs;              // Il numero di volte in cui il debitore è stato in ritardo di oltre 30 giorni con i pagamenti negli ultimi 2 anni
    int pub_rec;                  // Il numero di registri pubblici in deroga del mutuatario
    int not_fully_paid;           // 1 se il prestito non è stato completamente pagato; 0 altrimenti.
    float distance;               // Contiene la distanza con un altro loan
} loan_t;

loan_t *getLoansData(loan_t *, size_t, int);
void printLoan(const loan_t *);
int loanClassifier(loan_t *loans, int *n_loans, int k, const loan_t *loanToClassify);
int compareDistance(const void *a, const void *b);
void printLoadingBar(int, int);

int main()
{
    printf("\e[?25l"); //Nascondo il cursore
    // Creazione vettore di prestiti su cui effettuare il training dell'algoritmo
    loan_t *training_loans;
    loan_t *testing_loans;
    // Alloco spazio dinamico sia per i training che per i testing, 
    
    //siccome incremento il numero di elementi durante la classificazione dei prestiti di training alloco lo spazio massimo  per i prestiti
    if ((training_loans = (loan_t *)malloc(sizeof(loan_t) * MAX_LOANS)) == NULL)
    {
        puts("Non hai abbastaza spazio in memoria per eseguire il programma");
        return 0;
    }
    if ((testing_loans = (loan_t *)malloc(sizeof(loan_t) * N_TESTING_LOANS)) == NULL)
    {
        puts("Non hai abbastaza spazio in memoria per eseguire il programma");
        return 0;
    }

    //Ottengo i dati sui prestiti
    getLoansData(training_loans, N_TRAINING_LOANS, 1);
    getLoansData(testing_loans, N_TESTING_LOANS, N_TRAINING_LOANS + 1);

    int verified = 0;
    int notVerified = 0;
    int loadingStatus = 0;  //Variabile che mi tiene conto della percentuale di caricamento
    int nTrainingLoans = N_TRAINING_LOANS;  //Numero di prestiti nel training (vengono aggiunti al conto)
    puts("Calcolo in corso...");
    printf("%d%%", loadingStatus);
    for (int i = 0; i < N_TESTING_LOANS; i++)
    {
        int class = loanClassifier(training_loans, &nTrainingLoans, K_VALUE, &testing_loans[i]);
        //Incremento la barra di caricamento
        if(i % (N_TESTING_LOANS / 100) == 0)
        {
            CLEAR;
            loadingStatus++;
            puts("Calcolo in corso...");
            printf("%d%%\t", loadingStatus);
            printLoadingBar(loadingStatus, 20); //Stampo la barra di caricamento
            puts(""); //vado a capo
        }
        #ifdef DEBUG
        printf("%d: ", i);
        #endif
        if (class == testing_loans[i].credit_policy)
        {
            #ifdef DEBUG
            puts("Verificato");
            #endif
            verified++;
        }
        else
        {
            #ifdef DEBUG
            puts("Non verificato: ");
            puts("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
            printf("Classe: %d\n", testing_loans[i].credit_policy);
            for(int j = 0; j < K_VALUE; j++)
            {
                printf("Distance %d: %5.3f Class: %d\n", j + 1, training_loans[j].distance, training_loans[j].credit_policy);
            }
            printf("Classificato come: %d\n", class);
            puts("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
            #endif
            notVerified++;
        }
    }
    printf("\nNumero di prestiti classificati correttamente: %d\nNumero di prestiti non classificati correttamente: %d\n", verified, notVerified);
    printf("\nAccuratezza dell'%0.2f%%\n\n", ((float)verified / N_TESTING_LOANS) * 100);
    puts("FINE, premi INVIO per continuare");
    free(training_loans);
    free(testing_loans);
    getchar();
    return 0;
}

/**
 * Funzione che compara la distanza tra due punti LOAN
 * Utilizzata nella funzione qsort()
 *
 * Ritorna 1 se a > b
 * Ritorna -1 se a < b
 * Ritorna 0 se a = b
 */
int compareDistance(const void *a, const void *b)
{
    loan_t *x = (loan_t *)a;
    loan_t *y = (loan_t *)b;
    if (x->distance < y->distance)
        return -1;
    else if (x->distance > y->distance)
        return 1;
    else
        return 0;
}

//Funzione che classifica i prestiti secondo l'algoritmo KNN, mentre classifica aggiunge il prestito all'array, che deve essere inizializzato per contenere il numero totale di prestiti
int loanClassifier(loan_t loans[], int *n_loans, int k, const loan_t *loanToClassify)
{
    // Calcolo la distanza tra il mio punto e tutti i punti del training set. Uso dei pesi indicativi per rendere più accurato l'algoritmo
    for (int i = 0; i < *n_loans; i++)
    {
        loans[i].distance =
            (1.0 * sqrt(((double)loans[i].installment - (double)loanToClassify->installment) * ((double)loans[i].installment - (double)loanToClassify->installment))) +
            (1.0 * sqrt(((double)loans[i].fico - (double)loanToClassify->fico) * ((double)loans[i].fico - (double)loanToClassify->fico))) +
            (50.0 * sqrt(((double)loans[i].log_annual_inc - (double)loanToClassify->log_annual_inc) * ((double)loans[i].log_annual_inc - (double)loanToClassify->log_annual_inc))) +
            (100.0 * sqrt(((double)loans[i].not_fully_paid - (double)loanToClassify->not_fully_paid) * ((double)loans[i].not_fully_paid - (double)loanToClassify->not_fully_paid))) +
            (1000.0 * sqrt(((double)loans[i].int_rate - (double)loanToClassify->int_rate) * ((double)loans[i].int_rate - (double)loanToClassify->int_rate))) +
            (10.0 * sqrt(((double)loans[i].dti - (double)loanToClassify->dti) * ((double)loans[i].dti - (double)loanToClassify->dti))) +
            (0.1 * sqrt(((double)loans[i].days_with_cr_line - (double)loanToClassify->days_with_cr_line) * ((double)loans[i].days_with_cr_line - (double)loanToClassify->days_with_cr_line))) +
            (0.1 * sqrt(((double)loans[i].revol_bal - (double)loanToClassify->revol_bal) * ((double)loans[i].revol_bal - (double)loanToClassify->revol_bal))) +
            (10.0 * sqrt(((double)loans[i].revol_util - (double)loanToClassify->revol_util) * ((double)loans[i].revol_util - (double)loanToClassify->revol_util))) +
            (100.0 * sqrt(((double)loans[i].inq_last_6mths - (double)loanToClassify->inq_last_6mths) * ((double)loans[i].inq_last_6mths - (double)loanToClassify->inq_last_6mths))) +
            (100.0 * sqrt(((double)loans[i].delinq_2yrs - (double)loanToClassify->delinq_2yrs) * ((double)loans[i].delinq_2yrs - (double)loanToClassify->delinq_2yrs))) +
            (100.0 * sqrt(((double)loans[i].pub_rec - (double)loanToClassify->pub_rec) * ((double)loans[i].pub_rec - (double)loanToClassify->pub_rec)));
    }
    // Metto in ordine tutti i loans in base alla distanza
    qsort(loans, *n_loans, sizeof(loan_t), compareDistance);

    // Inizializzo il mio contatore di prestiti favorevoli e non favorevoli per la policy
    int count_favorable = 0;
    int count_not_favorable = 0;

    // Se i vicini k rispettano la policy incremento il contatore count_favorable, altrimenti il non_favorable
    for (int i = 0; i < k; i++)
    {
        if (loans[i].credit_policy)
            count_favorable++;
        else
            count_not_favorable++;
    }
    loans[*n_loans++] = *loanToClassify;  //Aggiungo il prestito nella lista, così da poter essere elaborato con tutti gli altri
    // Confronto se il nodo ha più vicini favorevoli al prestito o più sfavorevoli
    if (count_favorable > count_not_favorable)
        return 1;
    else
        return 0;
}

//Funzione che effettua la lettura dei dati di prestito
loan_t *getLoansData(loan_t loans[], size_t nLoans, int startingRow)
{
    // Ottenere dati da file
    FILE *f_credits = fopen("./credits.csv", "r");
    if (f_credits == NULL)
    {
        puts("Impossibile aprire il file!");
        exit(1);
    }

    // Leggo il file in modo tale da far scorrere il pointer fino alla riga desiderata
    for (int i = 0; i < startingRow; i++)
    {
        char str_row[256] = {0};
        fgets(str_row, 255, f_credits);
    }

    // Leggo ogni riga del file
    for (int i = 0; i < nLoans; i++)
    {
        // Ottengo la riga corrente del file
        char str_row[256] = {0};
        char *tmp_str;
        fgets(str_row, 255, f_credits); // Leggo la riga e la inserisco in una variabile tmp str_row
        tmp_str = strtok(str_row, ",");
        // Inserisco i valori della riga nella struct
        for (int j = 0; tmp_str != NULL; j++)
        {
            // In base al valore di j, inserisco i valori dei campi nel file all'interno della struttura
            switch (j)
            {
            case 0:
                loans[i].credit_policy = atoi(tmp_str); // Non faccio nessun controllo particolare siccome sono sicuro do avere valori numerici
                break;
            case 1:
                strcpy(loans[i].purpose, tmp_str);
                break;
            case 2:
                loans[i].int_rate = atof(tmp_str);
                break;
            case 3:
                loans[i].installment = atof(tmp_str);
                break;
            case 4:
                loans[i].log_annual_inc = atof(tmp_str);
                break;
            case 5:
                loans[i].dti = atof(tmp_str);
                break;
            case 6:
                loans[i].fico = atoi(tmp_str);
                break;
            case 7:
                loans[i].days_with_cr_line = atof(tmp_str);
                break;
            case 8:
                loans[i].revol_bal = atoi(tmp_str);
                break;
            case 9:
                loans[i].revol_util = atof(tmp_str);
                break;
            case 10:
                loans[i].inq_last_6mths = atoi(tmp_str);
                break;
            case 11:
                loans[i].delinq_2yrs = atoi(tmp_str);
                break;
            case 12:
                loans[i].pub_rec = atoi(tmp_str);
                break;
            case 13:
                loans[i].not_fully_paid = atoi(tmp_str);
                break;
            }
            loans[i].distance = 0.0; // Setto la distanza a 0
            tmp_str = strtok(NULL, ",");
        }
    }
    fclose(f_credits);
    return loans;
}


//Funzione che stampa la barra di caricamento
void printLoadingBar(int percentage, int length)
{
    if(length > 100)
        return;
    putchar('[');
    int stopSymbolLoad = percentage / (100 / length);
    for(int i = 0; i < length; i++)
    {
        if(i < stopSymbolLoad)  //Stampo finchè non raggiunge la percentuale dei cancelletti
            putchar('#');
        else
            putchar(' ');
    }
    putchar(']');
}