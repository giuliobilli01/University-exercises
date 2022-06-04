/*
 * Esercizio 2: Linguaggio C: 10 punti
 *	Estendere la soluione dell'esercizio 1: mmsleep (multimsleep) ammette molteplici parametri.
 *	msleep 1234 3456 2345
 *	allo scadere di 1234 millisecondi stampa 1234, allo scadere di 2345 millisecondi stampa 2345 e infine a 3456
 *	millisecondi dalla attivazione stampa 3456 ed esce.
 *	Questo programma deve essere implementato creando un timerfd per ogni parametro e usando poll(2) per
 *	aspettare il prossimo evento.
 * 
 *
 */

#include <sys/timerfd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <poll.h>



int main(int argc, char*argv[]) {
	struct pollfd timerPollFd[argc - 1];
	struct itimerspec specs[argc - 1];
	int timesInMs[argc - 1];
	// Creiamo il timer e salviamo il suo file descriptor per
	// ogni valore in input
	for (int i=0; i < argc - 1; i++) {
	timerPollFd[i].fd=timerfd_create(CLOCK_REALTIME, 0);
	timerPollFd[i].events = POLLIN;
	// E' un campo di ritorno e diventa != 0
	// in base al numero di fd che hanno completato
	// il loro task.

	timerPollFd[i].revents = 0;
	timesInMs[i] =(int)atoi(argv[i+1]);
	float parteInteraSec= timesInMs[i]/1000;
	float parteDecimaleSec=(timesInMs[i] % 1000)/1000;
	float nanosec=parteDecimaleSec* 1000000000;
	specs[i].it_value.tv_sec= parteInteraSec;
	specs[i].it_value.tv_nsec = nanosec;

	//spec.it_interval se settato a 0, il timer espirerà solo
	// una volta, mentre se è settato a un valore != 0 specifica il periodo
	// per timer ripetuti.
	specs[i].it_interval.tv_sec = 0;
	specs[i].it_interval.tv_nsec = 0;
	
	timerfd_settime(timerPollFd[i].fd, 0, &specs[i], NULL);
	printf("Timer %d started\n", timesInMs[i]);

	}
	int i=0;
	int timers = argc -1;
	while (timers > 0) {
		int numOfEvents = poll(&timerPollFd[i],1, -1);
		if(numOfEvents > 0) {
			uint64_t buf;
			ssize_t size;
			size= read(timerPollFd[i].fd, &buf, sizeof(uint64_t));
			if (size != sizeof(uint64_t))
				printf("Error: read\n");
			printf("Timer expired after %d ms\n", timesInMs[i]);
			i++;
			timers--;
		}
	}
	for(int i=0; i<argc; i++) {
		close(timerPollFd[i].fd);
	}
	return 0;

}

