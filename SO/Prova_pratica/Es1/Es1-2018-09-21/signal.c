/*
 * Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Lo scopo di questo esercizio è di scrivere un programma che usando la system call signalfd quando riceve un
 *	segnale SIGUSR1 o SIGUSR2 scriva in un file della directory corrente con nume uguale al pid del processo che ha
 *	inviato il segnale, il tipo di segnale ricevuto e l'ora esatta di ricezione del segnale. (se il file non esiste deve essere
 *	creato).
 *	un esempio di file risultante potrebbe essere:
 *	$ cat 20231
 *	USR1 Fri Sep 21 10:40:56 CEST 2018
 *	USR1 Fri Sep 21 10:40:58 CEST 2018
 *	USR2 Fri Sep 21 10:41:26 CEST 2018
 *
 *
 */

#include <limits.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define _OPEN_SYS_ITOA_EXT

int main(int argc, char*argv[]) {
	sigset_t mask;
	int sfd;
	struct signalfd_siginfo fdsi;
	ssize_t s;
	pid_t mainProc = getpid();
	// Settiamo la mask su i segnali da ricevere
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
	
	if (fork() != 0){
		// Tramite sigprocmask cambiamo la signal mask
		// standard con quella appena creata
		if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
			handle_error("sigprocmask");
	
		// Creiamo il file descriptor per accetare i segnali
		// indicati dalla mask
		sfd = signalfd(-1, &mask, 0);
		if (sfd == -1)
			handle_error("signalfd");
		// Creiamo il ciclo per ricevere i segnali tramite
		// read()
		for (;;) {
			s = read(sfd, &fdsi, sizeof(fdsi));
			if (s != sizeof(fdsi))
				handle_error("read");

			if (fdsi.ssi_signo == SIGUSR1) {
				char fileName[10];
				time_t currentTime = time(NULL);
				printf("Got SIGUSR1\n");
				// Creiamo il nome del file
				sprintf(fileName, "%d", fdsi.ssi_pid);
				FILE*file = fopen(fileName,"a");
				char* time_str=ctime(&currentTime);
				time_str[strlen(time_str)-1] = '\0';
				fprintf(file, "USR1 %s\n", time_str);
				fclose(file);
			} else if (fdsi.ssi_signo == SIGUSR2) {
				printf("Got SIGUSR2\n");
				char fileName[10];
				time_t currenTime = time(NULL);
				printf("Got SIGUSR2\n");
				// Creiamo il nome del file
				sprintf(fileName, "%d", fdsi.ssi_pid);
				FILE*file = fopen(fileName,"a");
				char* time_str=ctime(&currenTime);
				time_str[strlen(time_str)-1] = '\0';
				fprintf(file, "USR2 %s\n", time_str);
				fclose(file);
			 } else {
			    printf("Read unexpected signal\n");
		    }
		}
	}else {
		// Creiamo due processi per testare i signal
		pid_t firstProc;
		pid_t secondProc;

		firstProc = fork();
		if (firstProc == 0) {
			printf("Entered in first process with pid %d\n", getpid());
			kill(mainProc, SIGUSR1);
			exit(EXIT_SUCCESS);
		}

		secondProc = fork();
		if (secondProc == 0) {
			printf("Entered in second process with pid %d\n", getpid());
			kill(mainProc, SIGUSR2);
			exit(EXIT_SUCCESS);
		}
	}
    return 0;
}


