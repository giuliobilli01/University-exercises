/*
 *
 *
 *Esercizio 2: Linguaggio C: 10 punti
	Estendere la soluzione dell'esercizio 1: Modificare il programma dell'esercizio 1 per fare in modo che alla partenza
	scriva il proprio pid nel file /tmp/countpid. Scrivere poi un secondo programma che lanci il comando con argomenti
	passato come parametro, prima di eseguire il comando deve mandare SIGUSR1 al programma dell'esercizio 1, al
	termine deve mandare SIGUSR2.
	e.g.
	count sleep 20
	... spedisce SIGUSR1, esegue sleep 20, manda SIGUSR2. In questo modo il programma dell'esercizio 1 dovrebbe
	contare quanti comandi lanciati con il prgramma count sono in corso di esecuzione.
 *
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>


int main(int argc, char*argv[]) {
	// Estraiamo il comando in input
	char*args[argc];
	int i=1;
	while (i < argc && argv[i]!= NULL) {
		args[i-1] = argv[i];
		i++;
	}
	args[i]=NULL;
	// Deve inviare un segnale SIGUSR1
	// Prendiamo il pid del processo a cui mandarlo
	FILE*targetFile=fopen("/tmp/countpid.txt", "r");
	if (targetFile == NULL) {
		printf("File doesn't found.\n");
        exit(EXIT_FAILURE);
	}
	char targetPid[10];
	fgets(targetPid, 10, targetFile);
		
	// Convertiamo il pid in intero
	int pid= atoi(targetPid);
	printf("Pid: %d\n", pid);
	if (kill(pid, SIGUSR1) == -1 ) {
		printf("Error during message sending\n");
		exit(EXIT_FAILURE);
	}	

	// Eseguire il comando in input
	pid_t child;
	if ((child = fork()) == 0) {
		int status= execvp(args[0], args);  
		if (status == -1) printf("errore");	
	}
	printf("Command %s executed succesfully\n", args[0]);
	// Inviare un'altro segnale
	if (kill(pid, SIGUSR2) == -1 ) {
		printf("Error during message sending\n");
		exit(EXIT_FAILURE);
	}	
	return 0;
}

