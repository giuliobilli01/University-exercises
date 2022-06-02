/*
 *Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Usando inotify creare il programma neverm che controlli una directory. Ogni volta che viene
 *	cancellato un file nella directory sotto osservazione crei un file vuoto di uguale nome. Per esempio
 *	eseguendo
 *	neverm dir
 *	dove dir e' una directory contenente i file a, b, c, anche a seguito dei comandi 'rm dir/a' e 'rm dir/b',
 *	dir deve contenere sempre i file a, b e c, a e b saranno file vuoti.
 *
 *
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (1024 * ( EVENT_SIZE + 16))

int main(int argc, char*argv[]){
	// Prendiamo il nome della directory da controllare
	char dir[PATH_MAX];
	strcpy(dir, argv[1]);
	/*Viene utilizzato per salvare l'output di read*/
	int numberOfEvents = 0;
  
	/*Variabile per salvare il file descriptor che fa riferimento all'istanza di inotify*/
	int fd;
  
	/*Variabile per salvare il watch descriptor*/
	 int wd;

	 /*Buffer per leggere gli eventi  che si verificano*/
	 char buffer[EVENT_BUF_LEN];

	 // Inizializziamo l'istanza di inotify
	 fd = inotify_init();
  
	 // Controlliamo se l'istanza è stata creata correttamente
	if (fd < 0) perror("inotify_init");

	// Aggiungiamo alla watch list la directory exec da controllare
	wd = inotify_add_watch(fd, dir, IN_DELETE);

	// A questo punto se non ci sono stati errori numberOfEvents 
	// tiene il conto degli eventi avvenuti
	// e il buffer contiene gli eventi 
	while (numberOfEvents = read(fd, buffer, EVENT_BUF_LEN)){
		if (numberOfEvents < 0) perror("read");
		int i=0;
		while (i < numberOfEvents) {
			// Si può accedere ai campi dell'event per ricavare    informazioni utili
			struct inotify_event* event = (struct inotify_event*) &buffer[i];
			if (event->mask & IN_DELETE) {
				// Se il file viene rimosso bisogna ricrearlo
				char filePath[PATH_MAX];
				strcpy(filePath, dir);
				strcat(filePath, "/");
				strcat(filePath, event->name);
				// Creiamo il file con permessi: rw-rw-rw-
				close(creat(filePath, 0666));
				printf("Recreated file: %s\n", filePath);
			}
			i += EVENT_SIZE + event->len;
		}
	}
	inotify_rm_watch(fd, wd);
	close(fd);
	return 0;
}

