/**
 * @file prodcons.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Usando pthread_create occorre creare due thread che chiameremo produttore e consumatore.
Il thread produttore ripetutamente genera un numero causuale, lo stampa lo mette in una variabile
condivisa con il consumatore e attende (ritardo casuale). Il thread consumatore legge dalla variabile
condivisa i valori e li stampa (anche il consumatore attende per un periodo casuale prima di tentare di
leggere il valore successivo)
Ogni valore prodotto deve venir consumato una e una sola volta, per la sincronizzazione si richiede di
usare eventfd in modalità EFD_SEMAPHORE.
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <time.h>

// Ricordarsi di compilare con gcc -c -lpthread

// Puntatore alla variabile condivisa
int *val;

// I due file descriptor utilizzati per i semafori
int eventfdProd;
int eventfdCons;

// Buffer per read e write
uint64_t buf;

void* consumerFunction(void* arg) {
  int readedValue;
  int readedNumbers=10;
  while (readedNumbers > 0) {
    // Se il consumatore può leggere
    if (read(eventfdCons, &buf, sizeof(buf)) > 0) {
      readedValue = *val;
      readedNumbers--;
      printf("Readed number: %d\n", readedValue);
      write(eventfdProd, &buf, sizeof(buf));
      sleep(rand() % 10 + 1);
    }
  }
  return NULL;
}

void* producerFunction(void* arg) {
  int number=0;
  int generatedNumbers=10;

  while (generatedNumbers > 0) {
    // Se il produttore può iniziare a produrre
    if (read(eventfdProd, &buf, sizeof(buf)) > 0) {
      // Produco il numero casuale
      srand(time(NULL));
      do {
        number = rand() % 100 + 1;
      }while(number == *val);

      generatedNumbers--;
      printf("Produced number: %d\n", number);
      *val = number;
      // Rilascio della variabile condivisa
      write(eventfdCons, &buf, sizeof(buf));
      // Attende 
      sleep(rand() % 10);
    }
  }
  return NULL;
}

int main(int argc, char*argv[]) {
  // Allochiamo uno spazio di memoria per la variabile condivisa
  val = (int* )malloc(sizeof(int));
  // Thread per il consumatore e il produttore
  pthread_t consumer;
  pthread_t producer;

  // Inizializziamo i semafori per produttore e consumatore
  // Il consumatore parte con valore 0
  // in quanto non è ancora stato prodotto nulla
  eventfdCons = eventfd(0, EFD_SEMAPHORE);
  
  // Il produttore parte con valore 1 in  
  // quanto è il primo a dover partire
  eventfdProd = eventfd(1, EFD_SEMAPHORE);

  // Creiamo i due thread
  int succesfullStartProd;
  int succesfullStartCons;

  succesfullStartProd = pthread_create(&producer, NULL, producerFunction, NULL);
  if (succesfullStartProd != 0) printf("Error during creation of producer thread\n");

  succesfullStartCons = pthread_create(&consumer, NULL, consumerFunction, NULL);
  if (succesfullStartCons != 0) printf("Error during creation of consumer thread\n");

  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);

  printf("Task completed\n");
  exit(EXIT_SUCCESS);

}