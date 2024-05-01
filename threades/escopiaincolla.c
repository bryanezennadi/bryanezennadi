#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
int byteletti;
// Funzione eseguita dal thread di lettura
void *readFile(void *arg)
{
    char nomefile[50];
    strcpy(nomefile, (char *)arg); //il nome viene assegnato da argv al file

    FILE *source_file = fopen(nomefile, "rb");
  
    //lettura contenuto
    byteletti=fread(buffer, 1, BUFFER_SIZE, source_file);
    // Chiudi i file e termina il thread
    fclose(source_file);
    pthread_exit(NULL);
}
void *scrivifile(void *arg)
{
    char nomefile[50];
    strcpy(nomefile, (char *)arg); //il nome del file viene preso da argv

    FILE *destinazione = fopen(nomefile, "wb");
    //stampa su file di solo byte letti
    fwrite(buffer, 1, byteletti, destinazione);
    //chiusura file
    fclose(destinazione);
    //fine thread
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t lettura, scrittura;

    // Verifica che siano stati forniti argomenti sufficienti
    if (argc != 3)
    {
        printf("argomenti non inseriti da riga di comando, programma in chiusura\n");
        exit(0);
    }

    // Creazione del thread per la lettura
    if (pthread_create(&lettura, NULL, readFile, (void *)argv[1]) != 0)
    {
        printf("Errore nella creazione del thread di lettura");
        exit(0);
    }
    if (pthread_create(&scrittura, NULL, scrivifile, (void *)argv[2]) != 0)
    {
        printf("Errore nella creazione del thread di lettura");
        exit(0);
    }

    // Attendere il completamento del thread di lettura
    if (pthread_join(lettura, NULL) != 0)
    {
        printf("Errore nell'attesa del completamento del thread di lettura");
        exit(0);
    }

    printf("Il file è stato copiato con successo.\n");

    return 0;
}
