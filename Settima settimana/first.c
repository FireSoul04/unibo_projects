#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

#define N_TESTING_LOANS 2400
#define N_TRAINING_LOANS 7178
#define MAX_LOANS 9579
#define STRING_LENGTH 200
#define WORD_LENGTH 30
#define K_VALUE 7

// Nasconde il cursore della console
#define HIDE_CURSOR printf("\033[?25l")
// Partendo da x e y in input, sposta il cursore in quella posizione nella console
#define MOVE_CURSOR(x, y) (printf("\033[%d;%dH", (y), (x)))

typedef char string_t[STRING_LENGTH + 1];
typedef char word_t[WORD_LENGTH + 1];

typedef struct Loan {
    float init_rate, installment, log_annual_inc, dti, days_with_cr_line, revol_util, distance;
    int fico, revol_bal;
    bool credit_policy, inq_last_6mths, delinq_2yrs, pub_rec, not_fully_paid;
    word_t purpose;
} loan_t;

void print_loan(loan_t *);
void sort(loan_t *, int, int);
bool classify(loan_t *, loan_t *, int *, int, int);
loan_t* read_data(FILE *, int, int);
void swap(float *, float *);

int main() {
    int verified = 0;
    int not_verified = 0;
    int loan_index = N_TRAINING_LOANS;
    
    // Apro il file in lettura
    FILE *dataset = fopen("credits.csv", "r");
    if (dataset == NULL) {
        puts("Il dataset non è stato trovato...");
        exit(1);
    }

    loan_t *training_loans = read_data(dataset, MAX_LOANS, N_TRAINING_LOANS);
    loan_t *test_loans = read_data(dataset, N_TESTING_LOANS, MAX_LOANS);

    CLEAR;
    HIDE_CURSOR;
    for (int i = 0; i < N_TESTING_LOANS; i++) {
        if (classify(training_loans, &test_loans[i], &loan_index, MAX_LOANS, K_VALUE) == training_loans[i].credit_policy) {
            verified++;
        } else {
            not_verified++;
        }
        MOVE_CURSOR(0, 0);
        printf("Calcolando: %.2f%%", ((float)i / (N_TESTING_LOANS - 1)) * 100.0f);
    }
    
    printf("\nNumero di prestiti classificati correttamente: %d\nNumero di prestiti non classificati correttamente: %d\n", verified, not_verified);
    printf("\nAccuratezza dell'%.2f%%\n\n", ((float)verified / N_TESTING_LOANS) * 100.0f);
    free(training_loans);
    free(test_loans);
    system("pause");

    // Chiudo il file e ritorno l'array contenente tutti i dati del dataset
    fclose(dataset);

    return 0;
}

void swap(float *a, float *b) {
    float tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(loan_t *loans, int start, int end)
{
    float pivot = loans[start].distance;
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (loans[i].distance <= pivot)
            count++;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(&loans[pivotIndex].distance, &loans[start].distance);
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
    while (i < pivotIndex && j > pivotIndex) {
        while (loans[i].distance <= pivot) {
            i++;
        }
        while (loans[j].distance > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(&loans[i++].distance, &loans[j--].distance);
        }
    }
 
    return pivotIndex;
}
 
void sort(loan_t *loans, int start, int end)
{
    // base case
    if (start >= end)
        return;
    // partitioning the array
    int p = partition(loans, start, end);
    // Sorting the left part
    sort(loans, start, p - 1);
    // Sorting the right part
    sort(loans, p + 1, end);
}

// Controllo la distanza tra ogni dato del loan di test con il resto del dataset
bool classify(loan_t *loans, loan_t *test_loan, int *index, int n, int k) {
    // Calcolo la distanza euclidea tra il nuovo dato e i dati del dataset
    for (int i = 0; i < *index; i++) {
        loans[i].distance = sqrtf((loans[i].init_rate - test_loan->init_rate) * (loans[i].init_rate - test_loan->init_rate)
            + (loans[i].installment - test_loan->installment) * (loans[i].installment - test_loan->installment)
            + (loans[i].log_annual_inc - test_loan->log_annual_inc) * (loans[i].log_annual_inc - test_loan->log_annual_inc)
            + (loans[i].dti - test_loan->dti) * (loans[i].dti - test_loan->dti)
            + (loans[i].fico - test_loan->fico) * (loans[i].fico - test_loan->fico)
            + (loans[i].days_with_cr_line - test_loan->days_with_cr_line) * (loans[i].days_with_cr_line - test_loan->days_with_cr_line)
            + (loans[i].revol_bal - test_loan->revol_bal) * (loans[i].revol_bal - test_loan->revol_bal)
            + (loans[i].revol_util - test_loan->revol_util) * (loans[i].revol_util - test_loan->revol_util));
    }

    // Bubble sort
    sort(loans, 0, n - 1);

    // Mi salvo quante persone hanno la credit_policy favorevole rispetto ai dati del dataset
    int freq_fav = 0;
    int freq_not_fav = 0;
    for (int i = 0; i < k; i++) {
        if (loans[i].credit_policy) {
            freq_fav++;
        } else {
            freq_not_fav++;
        }
    }

    loans[*index] = *test_loan;
    *index++;
 
    return freq_fav > freq_not_fav;
}

// Funzione per leggere i dati del dataset
loan_t* read_data(FILE *dataset, int size, int end) {
    const char separator[2] = ",";
    
    // Alloco la memoria per tutte le righe del dataset
    loan_t *loans;
    if ((loans = (loan_t *) malloc(sizeof(loan_t) * size)) == NULL) {
        puts("Memoria non sufficente");
        exit(1);
    }

    // Stringa per dividere ogni cella
    char *token;
    // Mi salvo una stringa per salvare ogni cella del dataset
    string_t data;

    // Salta la prima riga
    fgets(data, STRING_LENGTH + 1, dataset);

    // Legge tutti i dati riga per riga
    for (int i = 0; fgets(data, STRING_LENGTH + 1, dataset) != NULL && i < end; i++) {
        // Gestisco ogni dato singolarmente
        token = strtok(data, separator);
        for (int j = 0; token != NULL; j++) {
            switch (j) {
            case 0:
                loans[i].credit_policy = (bool)atoi(token);
                break;
            case 1:
                sprintf(loans[i].purpose, "%s", token);
                break;
            case 2:
                loans[i].init_rate = atof(token);
                break;
            case 3:
                loans[i].installment = atof(token);
                break;
            case 4:
                loans[i].log_annual_inc = atof(token);
                break;
            case 5:
                loans[i].dti = atof(token);
                break;
            case 6:
                loans[i].fico = atoi(token);
                break;
            case 7:
                loans[i].days_with_cr_line = atof(token);
                break;
            case 8:
                loans[i].revol_bal = atoi(token);
                break;
            case 9:
                loans[i].revol_util = atof(token);
                break;
            case 10:
                loans[i].inq_last_6mths = (bool)atoi(token);
                break;
            case 11:
                loans[i].delinq_2yrs = (bool)atoi(token);
                break;
            case 12:
                loans[i].pub_rec = (bool)atoi(token);
                break;
            case 13:
                loans[i].not_fully_paid = (bool)atoi(token);
                break;
            }
            loans[i].distance = 0.0f;
            token = strtok(NULL, separator);
        }
    }

    return loans;
}