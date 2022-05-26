/**
 * @file lancia.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C (obbligatorio) 20 punti
 * Estendere l'esercizio 1. Il nuovo programma autolancia deve riconoscere se il primo parametro è una
libreria dinamica o un eseguibile gestendo entrambi i casi:
gcc -o hw hw.c
$ ./autolancia hw.so 1 2 3 4
hello world: hw.so 1 2 3 4
$ ./autolancia hw 1 2 3 4
hello world: hw.so 1 2 3 4

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
#include <sys/wait.h>

int isLibrary(char* argument) {
  int i=0;
  while (argument[i] != '\0') {
    if (argument[i] == '.') {
      return 1;
    }
    i++;
  }
  return 0;
}

int main(int argc, char*argv[]) {

  
  char firstArgument[40];
  char dir[PATH_MAX];
  char actualPath[PATH_MAX+1];

  getcwd(dir, sizeof(dir));
  strcat(dir, "/");
  strcat(dir, argv[1]);
  char* realPath = realpath(dir, actualPath);

  strcpy(firstArgument, argv[1]);
  if (isLibrary(firstArgument)) {

    void* handle = 0;
    char *error = NULL;
    
    //printf("%s", dir);

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
    // Contiamo gli argomenti in input
    int i=1;
    int elements=0;
    while (argv[i] != NULL) {
      elements++;
      i++;
    }

    
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
  }else {

    char execPath[PATH_MAX];
    strcpy(execPath, "./");
    int i=1;
    int elements=0;
    while (argv[i] != NULL) {
      elements++;
      i++;
    }
    
    char* arguments[elements+1]; 
    i=1;
    while (argv[i] != NULL) {
      arguments[i-1] = argv[i];
      printf("argument %s\n", arguments[i-1]);
      i++;
    }
    arguments[i-1] = NULL;
    strcat(execPath, arguments[0]);
    printf("%s\n", execPath);
    pid_t child;
        if ((child = fork()) == 0) {
          int status= execvp(execPath, arguments);
          if (status == -1) printf("errore");
        }
        wait(&child);
        exit(EXIT_SUCCESS);
  }

return 0;

}