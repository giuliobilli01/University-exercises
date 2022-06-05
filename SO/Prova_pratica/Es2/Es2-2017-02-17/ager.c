/*
 *
 *Esercizio 2: Linguaggio C: 10 punti
 *	Completare l’esercizio 1 ponendo una gestione opportuna dei parametri in linea comando che preveda di
 *	poter modificare solo la data di accesso o quella di modifica, di definire il tempo di “invecchiamento” e un help.
 *	Si possono inserire altri parametri ritenuti opportuni. 
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
	int haveToModifyAccessDate = 0;
	int haveToModifyModDate = 0;
	int isOnCurrentDir =0;
	int time = 864000;
	int option;

	while((option = getopt(argc, argv, "camht:")) != -1){
			switch(option) {
				case 'a':
					haveToModifyAccessDate = 1;
					break;
				case 'm':
					haveToModifyModDate = 1;
					break;
				case 'h':
					printf("This function change last modified time and last access time.\n"
							"Use:\n"
							"-a to change only last access time\n"
							"-m to modify only last mod time\n"
							"-t to set the time(default is ten days)\n"
							"-c to operate on the files in the current dir"
							"-h for help\n");
					break;
				case 't':
					time = atoi(optarg);
					break;
				case 'c':
					isOnCurrentDir=1;
					break;
				default:
					printf("Invalid option\n");
					exit(EXIT_FAILURE);
			}
		}
	// Se non ha paramteri in input
	// eseguiamo sulla directory corrente
	if (isOnCurrentDir == 1) {
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
				if (haveToModifyAccessDate) {
					fileStat.st_atime= fileStat.st_atime - time;
					newTime.actime = fileStat.st_atime;

				}
				if (haveToModifyModDate) {
					fileStat.st_mtime= fileStat.st_mtime - time;
					newTime.modtime = fileStat.st_mtime;
				}
				if (!haveToModifyModDate && !haveToModifyAccessDate) {
					fileStat.st_atime= fileStat.st_atime - time;
					newTime.actime = fileStat.st_atime;
					fileStat.st_mtime= fileStat.st_mtime - time;
					newTime.modtime = fileStat.st_mtime;
				}
				utime(filePath, &newTime);
			}
		}
	} else if (argc > 1 && isOnCurrentDir == 0) {
		for (int i=optind; i < argc; i++) {
			struct stat fileStat;
			if (stat(argv[i], &fileStat)==0) {
				struct utimbuf newTime;
				// 10 giorni in secondi = 864000
				if (haveToModifyAccessDate) {
					fileStat.st_atime= fileStat.st_atime - time;
					newTime.actime = fileStat.st_atime;

				}
				if (haveToModifyModDate) {
					fileStat.st_mtime= fileStat.st_mtime - time;
					newTime.modtime = fileStat.st_mtime;
				}
				if (!haveToModifyModDate && !haveToModifyAccessDate) {
					fileStat.st_atime= fileStat.st_atime - time;
					newTime.actime = fileStat.st_atime;
					fileStat.st_mtime= fileStat.st_mtime - time;
					newTime.modtime = fileStat.st_mtime;
				}
				utime(argv[i], &newTime);

			} else {
				printf("Error: stat\n");
				exit(EXIT_FAILURE);
			}
		}
	} 
	return 0;
}



