/**
 * @file shell.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C: 10 punti
Scrivere una shell minimale usando la libreria s2argv/execs (da scaricare da github).
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input
(^D).
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// compilare tutto con  gcc shell.c -L/home/your_user/path_to_library/build -l:libexecs.a
#include <execs.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearBuffer(char* buffer) {
  int i=0;
  while (buffer[i] != '\0') {
    buffer[i] = '\0';
    i++;
  }
}

int main(int argc, char*argv[]) {
  
  char commandsBuffer[1024];
  printf("Type in a command and its arguments, e.g ls -l\n");
  printf("Tip: if you want to run multiple commands separate commands with ';'\n");
  printf("Type logout to exit from shell\n");

  do {
    clearBuffer(commandsBuffer);
    printf(">");
    if (fgets(commandsBuffer, 1024, stdin) != NULL) {
      char **args= s2argv(commandsBuffer);
      if (strcmp(args[0], "logout") == 0) exit(EXIT_SUCCESS); 
      pid_t child;
        if ((child = fork()) == 0 && (strcmp(args[0], "logout") != 0)) {
          int status= execvp(args[0], args);
          if (status == -1) printf("errore");
        }
      wait(&child);
      s2argv_free(args);
    }
    printf("\n");
  }while(1);
  exit(EXIT_SUCCESS);
}