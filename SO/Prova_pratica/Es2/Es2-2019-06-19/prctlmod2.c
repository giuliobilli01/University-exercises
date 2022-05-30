/**
 * @file prctlmod.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C: 10 punti
Tramite l'opzione PR_SET_NAME sempre di prctl fare in modo che con il comando "ps -Leo pid,comm"
i nomi dei tre rpocessi creati dall'esercizio 1 compaiano con nome "nonno","figlio" e "nipote".
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[]){
  pid_t grandadPid = getpid();
  pid_t childPid;
  pid_t fatherPid;
  char name[30];
  int status;

  printf("pid nonno: %d\n",grandadPid);
  strcpy(name, "nonno");
  // Utilizziamo prctl per cambiare il comportamento
  prctl(PR_SET_NAME, name);
  prctl(PR_SET_CHILD_SUBREAPER, grandadPid);

  // Creiamo il processo padre figlio del nonno
  fatherPid = fork();
  // Nel caso in cui siamo nel processo appena creato
  if (fatherPid == 0) {
    printf("Entered in father process with pid %d\n", getpid()); 
    strcpy(name, "figlio");
    prctl(PR_SET_NAME, name);
    // Creiamo il processo nipote
    childPid = fork();
    // Nel caso in cui siamo nel processo figlio
    if (childPid == 0) {
      printf("Entered in child process with pid %d\n", getpid()); 
      strcpy(name, "nipote");
      prctl(PR_SET_NAME, name);
      sleep(50);
      printf("Exit from child process with pid %d\n", getpid());
      exit(EXIT_SUCCESS);
    }
    // Tornati nel processo padre termina anche lui
    sleep(10);
    printf("Exit from father process with pid %d\n", getpid());
    exit(EXIT_SUCCESS);
  }

  // Il processo nonno aspetta che termini 
  // prima il proccesso padre e poi
  // il processo figlio 
  pid_t wpid;
  waitpid(fatherPid, &status, 0);
  printf("Father process terminated\n");
  // Wait aspetta che un figlio del processo chiamante termini
  // in questo modo vediamo che il processo nipote informa della sua terminazione
  // il processo nonno
  wpid = wait(&status);
  printf("Child process with pid %d terminated\n", wpid);

return 0;
}