/**
 * @file paran.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C: 10 punti
estendere para a paran che ha un parametro che indica il numero massimo di esecuzioni concorrenti:
paran 3 sleep 20 // ls -l // ps // sleep 3
al max esegue 3 comandi in parallelo, quindi esegue i primi 3 comandi, qundo uno fra essi termina
ne attiva un successivo e cosi' via.
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


int main(int argc, char*argv[]) {
  int commandsNumber = countCommands(argv);
  int maxCommands= atoi(argv[1]);
  int status;
  command commands[commandsNumber];

  

  // Isoliamo i comandi in un array
  int i=2;
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
  int activeProcesses=0;
  pid_t processes[commandsNumber];

  for (int p=0; p < commandsNumber; p++) {
    if (activeProcesses > maxCommands) {
      wait(&status);
      activeProcesses--;
    }
    activeProcesses++;
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