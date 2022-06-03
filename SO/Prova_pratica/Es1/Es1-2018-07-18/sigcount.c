/*
 *
 *
 *	Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Lo scoopo di questo esercizio è di scrivere un programma che conti quanti segnali di tipo SIGUSR1 e quanti di tipo
 *	SIGUSR2 riceve. Ogni volta che riceve un segnale di tipo SIGUSR1 deve aumentare un contatore di 1, ogni volta
 *	che riceve SIGUSR2 deve decrementare di 1 il contatore. A ogni variazione del contatore il programma stampa il
 *	valore. Questo programma deve essere realizzato usando la system call signalfd.
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
	
	if(fork() != 0) {
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
		int sig1counter=0;
		int sig2counter=0;
		for (;;) {
			s = read(sfd, &fdsi, sizeof(fdsi));
			if (s != sizeof(fdsi))
				handle_error("read");
			if (fdsi.ssi_signo == SIGUSR1) {
				sig1counter++;
				printf("SIG 1: %d\n", sig1counter);
			} else if (fdsi.ssi_signo == SIGUSR2) {
				sig2counter++;
				printf("SIG 2: %d\n", sig2counter);	
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
			sleep(3);
			kill(mainProc, SIGUSR1);
			sleep(4);
			kill(mainProc, SIGUSR2);
			exit(EXIT_SUCCESS);
		}

		secondProc = fork();
		if (secondProc == 0) {
			printf("Entered in second process with pid %d\n", getpid());
			kill(mainProc, SIGUSR2);
			sleep(3);
			kill(mainProc, SIGUSR2);
			sleep(4);
			kill(mainProc, SIGUSR1);
			exit(EXIT_SUCCESS);
		}
	}
    return 0;
	}



