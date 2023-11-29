#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define K_ELEMENTS 7500
#define DATASET_LENGTH 10000
#define STRING_LENGTH 200
#define WORD_LENGTH 30

typedef char string_t[STRING_LENGTH + 1];
typedef char word_t[WORD_LENGTH + 1];

typedef struct Loan {
    float init_rate, installment, log_annual_inc, dti, days_with_cr_line, revol_util, distance;
    int fico, revol_bal;
    bool credit_policy, inq_last_6mths, delinq_2yrs, pub_rec, not_fully_paid;
    word_t purpose;
} loan_t;

void print_loan(loan_t *);
void sort(loan_t *, int);
bool classify(loan_t *, loan_t *, int, int);
loan_t* read_data();

int main() {
    loan_t *loans = read_data();
    loan_t test_loan = loans[K_ELEMENTS];
    if (classify(loans, &test_loan, DATASET_LENGTH, K_ELEMENTS) == test_loan.credit_policy) {
        for (int i = 0; i < DATASET_LENGTH; i++) {
            //print_loan(&loans[i]);
        }
    }
    print_loan(&test_loan);
    free(loans);
    system("pause");

    return 0;
}

void print_loan(loan_t *loan)
{
    printf("credit_policy: %d\n", loan->credit_policy);
    printf("purpose: %s\n", loan->purpose);
    printf("installment: %f\n", loan->installment);
    printf("log_actual_inc: %f\n", loan->log_annual_inc);
    printf("fico: %d\n", loan->fico);
    printf("not_fully_paid: %d\n", loan->not_fully_paid);
    printf("distance: %f\n", loan->distance);
}

// Bubble sort
void sort(loan_t *loans, int length) {
    bool sorted;
    do {
        sorted = true;
        for (int i = 0; i < length - 1; i++) {
            if (loans[i].distance > loans[i + 1].distance) {
                int distance = loans[i].distance;
                loans[i].distance = loans[i + 1].distance;
                loans[i + 1].distance = distance;
                sorted = false;
            }
        }
    } while(!sorted);
}

// Controllo la distanza tra ogni dato del loan di test con il resto del dataset
bool classify(loan_t *loans, loan_t *test_loan, int n, int k) {
    // Calcolo la distanza euclidea tra il nuovo dato e i dati del dataset
    for (int i = 0; i < n; i++) {
        loans[i].distance = sqrtf(powf(loans[i].init_rate - test_loan->init_rate, 2))
            + sqrtf(powf(loans[i].installment - test_loan->installment, 2))
            + sqrtf(powf(loans[i].log_annual_inc - test_loan->log_annual_inc, 2))
            + sqrtf(powf(loans[i].dti - test_loan->dti, 2))
            + sqrtf(powf(loans[i].revol_bal - test_loan->revol_bal, 2))
            + sqrtf(powf(loans[i].revol_util - test_loan->revol_util, 2));
    }

    // Bubble sort
    sort(loans, n);

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
 
    return freq_fav > freq_not_fav;
}

// Funzione per leggere i dati del dataset
loan_t* read_data() {
    const char separator[2] = ",";
    
    // Apro il file in lettura
    FILE *dataset = fopen("./loan_data.csv", "r");
    if (dataset == NULL) {
        puts("Il dataset non è stato trovato...");
        exit(1);
    }
    // Alloco la memoria per tutte le righe del dataset
    loan_t *loans = (loan_t *) malloc(sizeof(loan_t) * DATASET_LENGTH);

    // Stringa per dividere ogni cella
    char *token;
    // Mi salvo una stringa per salvare ogni cella del dataset
    string_t data;

    // Salta la prima riga
    fgets(data, STRING_LENGTH + 1, dataset);

    // Legge tutti i dati riga per riga
    for (int i = 0; fgets(data, STRING_LENGTH + 1, dataset) != NULL; i++) {
        // Gestisco ogni dato singolarmente
        token = strtok(data, separator);
        for (int j = 0; token != NULL; j++) {
            switch (j)
            {
            case 0:
                loans[i].credit_policy = (bool)atoi(data);
                break;
            case 1:
                strcpy(loans[i].purpose, data);
                break;
            case 2:
                loans[i].init_rate = atof(data);
                break;
            case 3:
                loans[i].installment = atof(data);
                break;
            case 4:
                loans[i].log_annual_inc = atof(data);
                break;
            case 5:
                loans[i].dti = atof(data);
                break;
            case 6:
                loans[i].fico = atoi(data);
                break;
            case 7:
                loans[i].days_with_cr_line = atof(data);
                break;
            case 8:
                loans[i].revol_bal = atoi(data);
                break;
            case 9:
                loans[i].revol_util = atof(data);
                break;
            case 10:
                loans[i].inq_last_6mths = (bool)atoi(data);
                break;
            case 11:
                loans[i].delinq_2yrs = (bool)atoi(data);
                break;
            case 12:
                loans[i].pub_rec = (bool)atoi(data);
                break;
            case 13:
                loans[i].not_fully_paid = (bool)atoi(data);
                break;
            }
            loans[i].distance = 0.0f;
            token = strtok(NULL, separator);
        }
    }

    // Chiudo il file e ritorno l'array contenente tutti i dati del dataset
    fclose(dataset);
    return loans;
}