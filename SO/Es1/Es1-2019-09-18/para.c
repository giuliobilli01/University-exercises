/**
 * @file para.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
scrivere un programma para per lanciare parallelamente comandi
para sleep 20 // ls -l // ps // sleep 3
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int countCommands(char *commands[]) {
  int i=0;
  int arg=1;
  while (commands[i] != NULL) {
    if (strcmp(commands[i], "//") == 0) {
      arg++;
    }
    i++;
  }
  return arg;
}

typedef struct command {
  char *arguments[20];
}command ;

int status;
int main(int argc, char*argv[]) {
  int commandsNumber = countCommands(argv);
  command commands[commandsNumber];

  // Isoliamo i comandi in un array
  int i=1;
  int c=0;
  int a=0;
  while (argv[i] != NULL) {
    if (strcmp(argv[i], "//") == 0) {
      commands[c].arguments[a] = NULL;
      c++;
      a=0;
      i++;
    } else {
    commands[c].arguments[a] = argv[i]; 
    i++;
    a++;
    }
  }
  commands[c].arguments[a] = NULL;

  // Eseguiamo i comandi in parallelo
  pid_t processes[commandsNumber];

  for (int p=0; p < commandsNumber; p++) {
    processes[p] = fork();
    if (processes[p] > 0) {
      execvp(commands[p].arguments[0], commands[p].arguments);
    }

  }
  pid_t wpid;
  while (wpid = wait(&status) >= 0)
    ;
  return 0;
}