/**
 * @file prctlmod.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Normalmente se un processo è orfano l'exit status viene ricevuto da init o systemd (processo 1).
Usando l'opzione PR_SET_CHILD_SUBREAPER della system call prctl(2) è possibile cambiare questo
comportamento.
Scrivere un programma che crei un processo figlio e uno nipote (tramite fork). Fare in modo che
termini prima il figlo e poi il nipote.
Il programma deve mostrare che con prctl/PR_SET_CHILD_SUBREAPER la terminazione del nipote
viene rilevata dal nonno.
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
  int status;

  printf("pid nonno: %d\n",grandadPid);
  // Utilizziamo prctl per cambiare il comportamento
  prctl(PR_SET_CHILD_SUBREAPER, grandadPid);

  // Creiamo il processo padre figlio del nonno
  fatherPid = fork();
  // Nel caso in cui siamo nel processo appena creato
  if (fatherPid == 0) {
    printf("Entered in father process with pid %d\n", getpid()); 
    // Creiamo il processo nipote
    childPid = fork();
    // Nel caso in cui siamo nel processo figlio
    if (childPid == 0) {
      printf("Entered in child process with pid %d\n", getpid()); 
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