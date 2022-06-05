/*
 *
 *Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Scrivere un programma ager in grado di invecchiare file.
 *	Il programma deve poter prendere una lista di file come parametri o nessun parametro, nel qual caso invecchierà
 *	tutti I file della directory corrente. “invecchiare” significa predatare il tempo di ultimo accesso e di modifica di 10
 *	giorni.
 *	Esempio:
 *	$ ls -l file
 *	-rw-r--r-- 1 renzo renzo 0 Feb 17 09:07 file
 *	$ ./ager file
 *	$ ls -l file
 *	-rw-r--r-- 1 renzo renzo 0 Feb 7 09:07 file
 *
 *
 *
 *
 *
 *
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

int main(int argc, char*argv[]) {
	
	// Se non ha paramteri in input
	// eseguiamo sulla directory corrente
	if (argc == 1) {
		char currentDir[PATH_MAX];
		DIR* dir;
		getcwd(currentDir, sizeof(currentDir));
		dir = opendir(currentDir);
		struct dirent *entry;
		if (dir == NULL){
			printf("Unable to read directory\n");
			exit(EXIT_FAILURE);
}
		while ((entry=readdir(dir)) != NULL) {
			if (entry->d_type & DT_REG) {
				char filePath[PATH_MAX];
				struct utimbuf newTime;
				strcpy(filePath, currentDir);
				strcat(filePath, "/");
				strcat(filePath, entry->d_name);
				// Prendiamo il tempo di modifica corrente del file
				struct stat fileStat;
				stat(filePath, &fileStat);
				// 10 giorni in secondi = 864000
        fileStat.st_atime= fileStat.st_atime - 864000;
        fileStat.st_mtime= fileStat.st_mtime - 864000;
				newTime.actime = fileStat.st_atime;
				newTime.modtime = fileStat.st_mtime;
				utime(filePath, &newTime);
			}
		}
	} else if (argc > 1) {
		for (int i=1; i < argc; i++) {
			struct stat fileStat;
			if (stat(argv[i], &fileStat)==0) {
				struct utimbuf newTime;
			// 10 giorni in secondi = 864000
        fileStat.st_atime= fileStat.st_atime - 864000;
        fileStat.st_mtime= fileStat.st_mtime - 864000;
				newTime.actime = fileStat.st_atime;
				newTime.modtime = fileStat.st_mtime;
				utime(argv[i], &newTime);

			} else {
				printf("Error: stat\n");
				exit(EXIT_FAILURE);
			}
		}
	} 
	return 0;
}



