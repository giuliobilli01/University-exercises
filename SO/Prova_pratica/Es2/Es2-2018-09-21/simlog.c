/*
 * Esercizio 2: Linguaggio C: 10 punti
 *	Dato un estratto di un file di log come questo:
 *	Sep 20 19:58:32 eipi ntpd[2051]: Listen normally on 99 eth0 [fe80::8456:a70]:123
 *	Sep 20 19:58:32 eipi ntpd[2051]: new interface(s) found: waking up resolver
 * 	Sep 20 19:58:34 eipi ntpd[2051]: Soliciting pool server 151.3.106.211
 *	Sep 20 19:58:35 eipi ntpd[2051]: Soliciting pool server 94.177.187.22
 *	Sep 20 19:58:48 eipi ntpd[2051]: Soliciting pool server 80.211.155.206
 *	Sep 20 19:58:49 eipi ntpd[2051]: Soliciting pool server 212.45.144.206
 *	Scrivere un programma che lo mostri alla stessa velocita' allla quale e' stato generato.
 *	In questo caso dovrebbe scrivere le prime dur righe, attendere 2 secondi, mostrare la terza, dopo un secondo la
 *	quarta quindi dopo una attesa di 13 secondi la quinta e la sesta dopo un ulteriore secondo.
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char*argv[]) {
	char filePath[PATH_MAX];
	strcpy(filePath, argv[1]);
	FILE* file= fopen(filePath, "r");

	if (file == NULL) {
		printf("File doesn't found.\n");
        exit(EXIT_FAILURE);
	}
	// Leggiamo il file riga per riga
	char lineToRead[150];
	int isFirstLine=0;
	char lineToStamp[150];
	int seconds=0, minutes=0;
	int prevSec=0, prevMin=0;
	char* token;
	int i=0;
	int timeToWait=0;
	
	while(fgets(lineToRead, 150, file)!= NULL ) {
    strcpy(lineToStamp, lineToRead);
		// Dobbiamo estrarre dalla stringa il tempo di ogni log
		token = strtok(lineToRead, " ");
		i=1;
		while (token != NULL && i <= 2) {
			token = strtok(NULL, " ");
			i++;
		}
		i=1;
		char *time[3];
		token=strtok(token, ":");
    time[0] = token;
		while (token != NULL) {
			token=strtok(NULL, ":");
			time[i]=token;
			i++;
		}
		minutes=atoi(time[1]);
		seconds=atoi(time[2]);
		if (isFirstLine == 0) {
			isFirstLine=1;
			prevSec=seconds;
			prevMin=minutes;
		}
		timeToWait=(seconds - prevSec)+60*(minutes - prevMin);
		sleep(timeToWait);
		printf("%s\n", lineToStamp);
		prevSec=seconds;
		prevMin=minutes;
	}

	fclose(file);
	return 0;
	
	}


