#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define LAST_DATA 2395
#define FIRST_DATA 7184
#define K 8
#define MAX_DATA_POINTS 9579
#ifdef _WIN32
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

// Partendo da x e y in input, sposta il cursore in quella posizione nella console
#define MOVE_CURSOR(x, y) (printf("\033[%d;%dH", (y), (x)))

struct point
{
   int idoneo; //prima colonna//
   float purpose; //seconda colonna//
   float installment;//quarta colonna//
   float log_annual_inc;//quinta colonna//
   float fico;//settima colonna//
   int pagato; //quattordicesima colonna//

};

struct nearest
{
    int elemento;  //riga nel file
    float distanza;  //distanza con il point del test
};

float distanza(float a1, float b1, float c1, float d1, int e1, float a2, float b2, float c2, float d2, int e2 )
{
    float distanza;
    distanza=sqrtf((a1-a2)*(a1-a2)+(b1-b2)*(b1-b2)+(c1-c2)*(c1-c2)+(d1-d2)*(d1-d2));
    return distanza;
}

void sort(struct nearest len[], int fine)
{
    //sort per cercare i nearest neighbours
    int appoggio, appoggio_2;
    int i, j;

    for (i=0; i<fine-1; i++)
    {
        for (j=i+1; j<fine; j++)
        {
            if(len[i].distanza>len[j].distanza)
            {
                appoggio=len[i].distanza;
                appoggio_2=len[i].elemento;
                len[i].elemento=len[j].elemento;
                len[j].elemento=appoggio_2;
                len[i].distanza=len[j].distanza;
                len[j].distanza=appoggio;
            }
        }
    }
}

int cerca_vicini(struct point arr[], struct nearest len[], int k)
{
    int classe_0=0, classe_1=0;
    int i;

    //puts("\ngli elementi piu' vicini sono i seguenti: ");
    for (i=0; i<k+1; i++)
    {
        //printf("\nclasse:%d\t elemento:%d", arr[len[i].elemento].pagato, len[i].elemento);

        if (arr[len[i].elemento].pagato == 1)
        {
            classe_1+=1;
        }
        else
        {
            classe_0+=1;
        }
    }

    if (classe_1>classe_0)
    {
        //puts("\n\nla classe secondo l'algoritmo e' quindi la 1");
        return 1;
    }
    else
    {
        //puts("\n\nla classe secondo l'algoritmo e' quindi la 0");
        return 0;
    }
}

int knn(struct point arr[], struct nearest len[], int da_cercare, int k, int* fine, struct point test, int lunghezza)
{
    int i, j;
    float dist;
    int classe_algo; // la classe secondo il knn
    int classe_data; // classe nel database

    for (j=0; j<*fine; j++)
    {
        // distanza euclidea
        dist=distanza(arr[da_cercare].purpose, arr[da_cercare].installment, arr[da_cercare].log_annual_inc, arr[da_cercare].fico, arr[da_cercare].idoneo, arr[j].purpose, arr[j].installment, arr[j].log_annual_inc, arr[j].fico, arr[j].idoneo);
        len[j].distanza=dist;
        len[j].elemento=j;
    }

    sort(len, lunghezza);

    classe_algo=cerca_vicini(arr, len, k); // Passo la parte ordinata di len
    classe_data=arr[da_cercare].pagato;

    //printf("\n\nla classe nel database e' la: %d", classe_data);
    //puts("");

    arr[*fine] = test;
    *fine++;

    if (classe_algo==classe_data)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void lettura_File(struct point arr[], int inizio, int fine, FILE* f){

    char riga[200];
    char *token;
    int num_riga = inizio, num_colonna;
    int i, j;


    if (f==NULL)
    {
        puts("errore nell'apertura del file");
        exit(1);
    }

    while ((fgets(riga, 200, f)!=NULL) && num_riga < fine) //riempio l'array di struct point con i dati del file
    {
        num_colonna=1;
        token=strtok(riga, ","); //cerco la prima colonna//

        while(num_colonna<15)
        {
            switch (num_colonna) {
                case 1:
                    arr[num_riga].idoneo=atoi(token);  //atoi trasforma una stringa(token) in un numero//
                    break;
                case 2:
                    if (strcmp(token, "credit_card") == 0)  //collego ogni purpose a un numero//
                    {
                        arr[num_riga].purpose = 7;
                    }

                    else if (strcmp(token, "all_other") == 0)
                    {
                        arr[num_riga].purpose = 2;
                    }

                    else if (strcmp(token, "home_improvement") == 0)
                    {
                        arr[num_riga].purpose = 3;
                    }

                    else if (strcmp(token, "small_business") == 0)
                    {
                        arr[num_riga].purpose = 4;
                    }

                    else if (strcmp(token, "major_purchase") == 0)
                    {
                        arr[num_riga].purpose = 5;
                    }

                    else if (strcmp(token, "educational") == 0)
                    {
                        arr[num_riga].purpose = 6;
                    }

                    else if (strcmp(token, "debt_consolidation") == 0)
                    {
                        arr[num_riga].purpose = 1;
                    }
                    break;
                case 4:
                    arr[num_riga].installment=atof(token);        //atof trasforma una stringa(token) in un double
                    break;
                case 5:
                    arr[num_riga].log_annual_inc=atof(token);
                    break;
                case 7:
                    arr[num_riga].fico=atof(token);
                    break;
                case 14:
                    arr[num_riga].pagato=atoi(token);
                    break;
            }
            token=strtok(NULL, ",");//cerca il prossimo elemento(prossima colonna)//
            num_colonna++;
        }
        num_riga++;
    }

}


int main()
{
    FILE *f;
    f=fopen("credits.csv","r");
    struct point arr[MAX_DATA_POINTS]; //array di tipo point che contiene tutti i dati del file
    struct nearest len[MAX_DATA_POINTS]; //array di tipo nearest che contiene le distanze tra i punti e il punto da testare
    struct point test[LAST_DATA];
    int fine = FIRST_DATA;
    int corretti = 0, errati = 0;

    lettura_File(arr, 1, FIRST_DATA, f);
    lettura_File(test, FIRST_DATA + 1, LAST_DATA, f);

    for (int i = 0; i < LAST_DATA + 1; i++){
        int classe = knn(arr, len, i, K, &fine, test[i], FIRST_DATA);
        if(classe == test[i].idoneo){

            corretti++;
        }
        else{

            errati++;

        }
        MOVE_CURSOR(0, 0);
        printf("Caricamento: %.2f%%", (float)(i*100)/LAST_DATA);
    }


    printf("\n\nLa precisione dell'algoritmo e': %.2f%%", (float)(corretti*100)/LAST_DATA);

    fclose(f);
    system("pause");
    return 0;

}
