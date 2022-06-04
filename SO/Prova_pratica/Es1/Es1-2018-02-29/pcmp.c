/*
 *
 *Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Fare un programma di confronto parallelo di file.
 *	pcmp file1 file2
 *	non stampa nulla se i due file sono uguali altrimenti stampa "file1 file2 differ". pcmp deve creare due processi figli;
 *	mentre un processo controlia la prima meta’ del file, l'altro deve controllare l’altra meta’.
 *	Se un dei due processi figli trova una differenza, termina immediatamente segnalandolo al padre con opportuno
 *	valore di ritorno. In questo caso il padre deve terminare l'altro processo.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int compareFiles(FILE* file1, FILE* file2, size_t startPoint, size_t blockSize, int processNumber) {
	fseek(file1, startPoint, SEEK_SET);
	fseek(file2, startPoint, SEEK_SET);
	printf("Block size: %ld\n", blockSize);
	char c1=getc(file1);
	char c2=getc(file2);
	size_t i=0;
	while (c1 != EOF && c2 != EOF && i<=blockSize) {
		i++;
		//printf("c1: %c id: %d \n", c1, processNumber);
		//printf("c2: %c id: %d \n", c2, processNumber);
		if (c1 != c2) {
			return 0;
		}
		c1 = getc(file1);
		c2 = getc(file2);
	}
	return 1;
}

int main(int argc, char*argv[]) {
	// Prendiamo i path dei due file
	char file1Path[PATH_MAX];
	char file2Path[PATH_MAX];
	int numberOfProcess=2;
	
	strcpy(file1Path, argv[1]);
	strcpy(file2Path, argv[2]);
	
	FILE* f1= fopen(file1Path, "r");
	FILE* f2= fopen(file2Path, "r");

	// Salviamo la dimensione dei file in byte in
	// modo da poterla dividere in due
	fseek(f1, 0L, SEEK_END);
	size_t sizeFile1= ftell(f1);

	fseek(f2, 0L, SEEK_END);
	size_t sizeFile2= ftell(f2);

	printf("Size of file 1: %ld", sizeFile1);
	printf("Size of file 2: %ld", sizeFile2);
	
	fseek(f1, 0L, SEEK_SET);
	fseek(f2, 0L, SEEK_SET);
	// Facciamo un primo controllo per vedere se sono
	// diversi in base alla size
	if (sizeFile1 != sizeFile2) {
		printf("%s %s differ", file1Path, file2Path);
		fclose(f1);
		fclose(f2);
		return 0;
	}

	// Determiniamo la dimensione dei blocchi in cui dividere
	// il file
	float blockSize= sizeFile1/numberOfProcess;
	
	//Creiamo due processi figli
	pid_t processes[numberOfProcess];
	
	for (int i=0; i < numberOfProcess; i++) {
		// Se siamo nel processo creato
		if ((processes[i] = fork())==0) {
			printf("Entro nel processo %d\n", i);
			// Controlliamo se i file sono diversi
			int res=compareFiles(f1, f2, blockSize*i, blockSize, i);
			// Exit termina il processo e ritorna al padre
			// res, ovvero il risultato della comparazione.
			printf("Res: %d", res);
			exit(res);
		}
	}
	// Nel processo padre con wait possiamo ottenere 
	// i valori mandati con exit().

	for (int i=0; i < numberOfProcess; i++) {
		int status;
		if (processes[i]> 0) {
			waitpid(processes[i], &status, 0);
			if (WIFEXITED(status)) {
				if (WEXITSTATUS(status) == 0) {
					printf("%s %s differ\n", file1Path, file2Path);
					for (int k=i; k < numberOfProcess; k++){
						kill(processes[k], SIGTERM);
					}
					fclose(f1);
					fclose(f2);
					return 0;
				}
			}
		}
	}
	printf("Files are equal\n");
	fclose(f1);
	fclose(f2);
	return 0;
	
	
}
