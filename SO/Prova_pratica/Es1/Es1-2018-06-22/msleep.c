/*
 *
 *Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Lo scopo di questo esercizioè di scrivere msleep. msleep si comporta come sleep(1) ma invece di attendere il
 *	numero di secondi indicati come parametro deve aspettare il numero di millisecondi indicati come parametro.d
 *	es:
 *	msleep 2340
 *	completa la sua esecuzione in 2340 millisecondi alias 2.34 secondi.
 *	La msleep deve essere implementata usando i timerfd (v. timerfd_create(2))
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


int main(int argc, char*argv[]) {
	// Creiamo il timer e salviamo il suo file descriptor
	int timerFd=timerfd_create(CLOCK_REALTIME, 0);
	
	if (timerFd > 0) {
		// Prendiamo il valore in input e lo convertiamo in intero
		int timeInMs= (int)atoi(argv[1]);
		float parteInteraSec= timeInMs/1000;
		float parteDecimaleSec=(timeInMs % 1000)/1000;
		float nanosec=parteDecimaleSec * 1000000000;
		printf("Tempo in sec: %f\n Tempo in nanosec: %f\n", parteInteraSec, nanosec);
		struct itimerspec spec;
		// spec.it_value specifica la scadenza iniziale del timer 
		// in secondi e in nanosecondi. Settare entrambi i valori con un valore 
		// != 0 fa partire il timer.
		spec.it_value.tv_sec = parteInteraSec;
		spec.it_value.tv_nsec = nanosec;
		//spec.it_interval se settato a 0, il timer espirerà solo
		// una volta, mentre seù settato a un valore != 0 specifica il periodo
		// per timer ripetuti.
		spec.it_interval.tv_sec = 0;
		spec.it_interval.tv_nsec = 0;

		timerfd_settime(timerFd, 0, &spec, NULL);
		printf("Timer started\n");


		uint64_t buf;
		ssize_t size;
		size= read(timerFd, &buf, sizeof(uint64_t));
			if (size != sizeof(uint64_t))
				printf("Error: read\n");
		
		
		printf("Timer expired after %d ms\n", timeInMs);
		
	} 
	return 0;
}
