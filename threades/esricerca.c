#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#define Dim_array 1000
int passaggio = 0;
int array[Dim_array];
int trovato;

void *TrovaNumero(void *arg)
{
    

    int ricercato = *((int *)arg);
    if (passaggio == 0)
    {

        passaggio++;
        for (int i = 0; i < Dim_array / 2; i++)
        {
            if (array[i] == ricercato)
            {
                printf("numero trovato posizione: %d\n", i);
                trovato = 1;
            }
        }
    }
    else
    {

        for (int i = Dim_array / 2; i < Dim_array; i++)
        {
            if (array[i] == ricercato)
            {
                printf("numero trovato posizione: %d \n", i);
                trovato = 1;
            }
        }
    }
  
    if (trovato == 0)
    {
        printf("numero non trovato\n");
    }
}
void main()
{
    int ricercato;
    do{
    printf("che numero cerchi? deve esser compreso tra 0 e 500\n");
    scanf("%d", &ricercato);
    }while(ricercato<0 || ricercato > 500);
    
    printf("------------------------------\n");
    // Inizializza il generatore di numeri casuali con il seme corrente
    srand(time(NULL));

    for (int i = 0; i < Dim_array; i++)
    {

        int minimo = 1;
        int massimo = 500;
        int numero_casuale;

        // Genera un numero casuale compreso tra minimo e massimo
        array[i] = minimo + rand() % (massimo - minimo + 1);
    }

    pthread_t thread1, thread2;                                               // dichiarazione variabili thread
    if (pthread_create(&thread1, NULL, TrovaNumero, (void *)&ricercato) != 0) // crea il thread, (indirizzo variabile, null, metodo void, variabile castata a void)
    {
        perror("ERRORE CREAZIONE THREAD 1\n");
        exit(-1);
    }
    if (pthread_create(&thread2, NULL, TrovaNumero, (void *)&ricercato) != 0)
    {
        perror("ERRORE CREAZIONE THREAD 2\n");
        exit(-1);
    }
    if (pthread_join(thread1, NULL) != 0)
    {
        perror("ERRORE THREAD 1 \n");
        exit(-1);
    }
    if (pthread_join(thread2, NULL) != 0) // se il thread non si chiude è erroe
    {
        perror("ERRORE THREAD 2\n");
        exit(-1);
    }
}