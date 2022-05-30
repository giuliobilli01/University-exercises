/**
 * @file lancia.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Sia dato questo programma hw.c (vi viene fornito in /public/hw.c)
#include <stdio.h>
int main(int argc, char*argv[]) {
printf("hello world:");
for(argv++, argv--; argc > 0; argv++, argc--)
printf(" %s",*argv);
printf("\n");
return 0;
}
Il programma hw.c può essere compilato come libreria dinamica:
gcc --shared -o hw.so hw.c
La libreria dinamica non è un eseguibile
$ ./hw.so 1 2 3 4
Segmentation fault
ma può essere caricata a tempo di esecuzione tramite dlopen. Scrivere un programma "lancia" in
grado di eseguire il codice di hw.so
$ ./lancia hw.so 1 2 3 4
hello world: hw.so 1 2 3 4
(suggerimenti: dlopen non cerca nella directory corrente, occorre passare il path assoluto della libreria.
"main" in hw.so è una normale funzione: occorre cercare l'indirizzo della funzione main nella libreria
ed invocarla,)
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char*argv[]) {
  void* handle = 0;
  char *error = NULL;
  char dir[PATH_MAX];
  char actualPath[PATH_MAX+1];

  getcwd(dir, sizeof(dir));
  //printf("%s", dir);
  strcat(dir, "/");
  strcat(dir, argv[1]);
  char* realPath = realpath(dir, actualPath);



  handle = dlopen(realPath, RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  // Eliminiamo gli errori esistenti
  dlerror();

  // Chiamiamo dlsym per recuperare l'indirizzo della funzione main
  void (*mainso)(int, char**);
  *(void **)(&mainso) = dlsym(handle, "main");
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  int i=1;
  int elements=0;
  while (argv[i] != NULL) {
    elements++;
    i++;
  }

  // Contiamo gli argomenti in input
  char* arguments[elements]; 
  i=1;
  while (argv[i] != NULL) {
    arguments[i-1] = argv[i];
    i++;
  }

  // Nel caso funzioni dobbiamo dare a main i valori in input
  arguments[i-1]=NULL;
  (*mainso)((int)argc - 1, arguments);
  dlclose(handle);
  exit(EXIT_SUCCESS);

}