/*
 *Esercizio 2: Linguaggio C: 10 punti
 *	modificare neverm per fare in modo che neverm ripristini anche il contenuto dei file a seguito della
 *	cancellazione (il modo è lasciato alla creatività del candidato)
 *
 *
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
#include <dirent.h>

#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (1024 * ( EVENT_SIZE + 16))

int getIndex(int inode, int maxRange){
	return inode%maxRange;
	}

typedef struct file{
	FILE* ptr;
	char name[150];
	} file_t;

FILE* getFile(file_t* files, int len, char* fileName){
	int i=0;
	while(i<len){
			if (strcmp(files[i].name, fileName)== 0){
				return files[i].ptr;
				}
			i++;
		}
		return NULL;
	} 

int main(int argc, char*argv[]){
	// Prendiamo il nome della directory da controllare
	char dir[PATH_MAX];
	strcpy(dir, argv[1]);

	// Apriamo la directory e apriamo tutti i file in modo da
	// non perdere il file descriptor quando viene eseguito rm.
	// I file vengono salvati in un array e verranno trovati tramite nome
	DIR* targetDir = opendir(dir);
	struct dirent *entry;
	file_t files[100];
	int i=0;
	if (targetDir == NULL){
		perror("Unable to read directory\n");
		exit(EXIT_FAILURE);
	}
	while ((entry=readdir(targetDir))) {
		if (entry->d_type & DT_REG) {
			char filePath[PATH_MAX];
			strcpy(filePath, dir);
			strcat(filePath, "/");
			strcat(filePath, entry->d_name);
			printf("Path: %s\n", filePath);
			files[i].ptr= fopen(filePath, "r");
			strcpy(files[i].name, entry->d_name);
			i++;
			}
	}
	closedir(targetDir);

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
				// Creiamo il file in scrittura e copiamo il contenuto
				// di quello eliminato
				FILE* destFile=fopen(filePath, "w");
				// Troviamo il file da ricopiare
				int k=0;
				int index=0;
				while(k<100){
					if (strcmp(files[k].name, event->name)== 0){
						index=k;
						break;
					}
					k++;
				}
				char c=fgetc(files[index].ptr);
				printf("char: %c\n", c);
				while (c != EOF) {
					fputc(c, destFile);
					c = fgetc(files[index].ptr);
				}
				fclose(destFile);
				fclose(files[index].ptr);
				printf("Recreated file: %s\n", filePath);
			}
			i += EVENT_SIZE + event->len;
		}
	}
	inotify_rm_watch(fd, wd);
	close(fd);
	return 0;
}




