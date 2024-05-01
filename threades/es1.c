#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
typedef struct
{
    char nome[20];
    char cognome[20];
    char classe[20];
    float media;
}Studente;
void *StampaConsole(void *t){
    Studente *stude = (Studente*)t;
    printf("dati: \n");
    printf("%s\n", stude->nome);
    printf("%s\n", stude->cognome);
    printf("%s\n", stude->classe);
    printf("%f\n", stude->media);
}
void *StampaFile (void *arg){
Studente *stud= (Studente*)arg;
    FILE *file= fopen("filedati","w");
    if(file==NULL)
    {
        perror("ERRORE CREAZIONE FILE\n");
        exit(-1);
    }
    fprintf(file, "Dati\n" );
    fprintf(file, "Nome: %s\n", stud->nome);
    fprintf(file, "Cognome: %s\n", stud->cognome);
    fprintf(file, "Classe: %s\n", stud->classe);
    fprintf(file, "Media: %.2f\n", stud->media);
    fclose(file);
}

void main(){
    Studente stud;
  printf("Inserisci nome studente:\n");
    scanf("%s",stud.nome);
    printf("Inserisci cognome studente:\n");
    scanf("%s",stud.cognome);
    printf("Inserisci classe studente:\n");
    scanf("%s",stud.classe);
    printf("Inserisci media studente:\n");
    scanf("%f",&stud.media);

    pthread_t thread1, thread2;    //dichiarazione variabili thread
    if(pthread_create(&thread1, NULL, StampaConsole,(void*)&stud)!=0) //crea il thread, (indirizzo variabile, null, metodo void, variabile castata a void)
    {
        perror("ERRORE CREAZIONE THREAD 1\n");
        exit(-1);
    }
    if(pthread_create(&thread2, NULL,StampaFile,(void*)&stud)!=0)
    {
        perror("ERRORE CREAZIONE THREAD 2\n");
        exit(-1);
    }
    if(pthread_join(thread1,NULL)!=0)
    {
        perror("ERRORE THREAD 1 \n");
        exit(-1);
    }
    if(pthread_join(thread2, NULL)!=0)      //se il thread non si chiude è erroe
    {
        perror("ERRORE THREAD 2\n");
        exit(-1);
    }
}