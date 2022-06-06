/*
 *Esercizio 2: Linguaggio C: 10 punti
 *	Completare il programma precedente in modo che classifichi I file in base al numero di nomi (link) che hanno.
 *	L’output deve indicare quanti file hanno un solo nome, quanti ne hanno due, tre e cosi’ via.
 *	Si devono tenere in considerazione solamente I link presenti all’interno del sottoalbero.
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int fileCounter;
int dirCounter;
int totalRep=1;
typedef struct inodeList {
	ino_t inode;
	int rep;
	struct inodeList* next;
}inodeList;

typedef inodeList* inodeList_ptr;
inodeList* head=NULL;

int isElementInList(inodeList* head, ino_t element) {
	printf("Element inode: %ld \n",element);
	if(head == NULL) {
		return 0;
	}else {
		inodeList* tmp = head;
		while (tmp!=NULL) {
			if (tmp->inode == element) {
				tmp->rep++;
				totalRep++;
				printf("List inode: %ld", tmp->inode);
				return 1;

			}
				
			tmp=tmp->next;
		}
		return 0;
	}
}

void insertElement(inodeList_ptr* head, ino_t inode) {
	inodeList_ptr newNode = (inodeList_ptr)malloc(sizeof(inodeList));
	newNode->inode = inode;
	newNode->rep = 1;
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
		return;
	}
	inodeList_ptr tmp = *head;
	while (tmp->next != NULL) {
		tmp=tmp->next;
	}
	tmp->next = newNode;
	return;
}

void recursivelyDirectoryExploration(char* rootDir) {
	// Lista per salvare gli inode dei file
	// incontrati
	DIR* dir=opendir(rootDir);
	if (dir == NULL) {
		printf("Error: unable to open directory \"%s\"\n", rootDir);
		exit(EXIT_FAILURE);
	}
	struct dirent* entry;

	while ((entry =readdir(dir))!= NULL) {
		// Esplorando il sottoalbero dobbiamo contare i
		// file
		
		// Se incontriamo una directory
		// dobbiamo entrarci
		if (entry->d_type & DT_DIR) {
			char newDir[PATH_MAX];
			strcpy(newDir, rootDir);
			strcat(newDir, "/");
			strcat(newDir, entry->d_name);
			if(!(strcmp(entry->d_name, "..")==0) && !(strcmp(entry->d_name, ".")==0)) {
				dirCounter++;
				recursivelyDirectoryExploration(newDir);
			}
			// Se è un file regolare
		} else if(entry->d_type & DT_REG) {
			// Controlliamo l'inode e vediamo se
			// lo abbiamo già incontrato
			if (!(isElementInList(head, entry->d_ino)==1)) {
				fileCounter++;
				insertElement(&head, entry->d_ino);
			}
			
		}
	}
}

int countRepOfNames(inodeList_ptr head, int numberOfNames) {
	int repCounter=0;
	inodeList* tmp = head;
	while (tmp!=NULL) {
		if (tmp->rep == numberOfNames) {
			repCounter++;
		}
		tmp=tmp->next;
	}
	return repCounter;
}

int main(int argc, char* argv[]) {
	char rootDir[PATH_MAX];
	if (argc > 1) {
		strcpy(rootDir, argv[1]);
		recursivelyDirectoryExploration(rootDir);
		printf("Number of files: %d\n", fileCounter);
		printf("Number of dir: %d\n", dirCounter);
		// Stampiamo i file in base al numero
		// di ripetizioni dei nomi
		for (int i=1; i <=1; i++) {
			printf("Files with %d name/s: %d\n",i, countRepOfNames(head, i));
		}

	}else {
		getcwd(rootDir, sizeof(rootDir));
		recursivelyDirectoryExploration(rootDir);
		printf("Number of files: %d\n", fileCounter);
		printf("Number of dir: %d\n", dirCounter);
		for (int i=1; i <=totalRep; i++) {
			printf("Files with %d name/s: %d\n",i, countRepOfNames(head, i));
		}
	}
}
