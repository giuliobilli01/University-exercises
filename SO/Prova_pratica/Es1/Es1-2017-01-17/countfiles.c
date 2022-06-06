/*
 *
 *Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Scrivere un programma che conti I file ordinari e le directory presenti nel sottoalbero della directory passata come
 *	parametro (o della directory corrente se non viene passato alcun parametro).
 *	Ogni file o directory deve venir contato una sola volta anche se e’ presente con diversi nomi a causa dei link fisici.
 *	Ogni altro tipo di file che non sia file ordinario o directory (e.g. socket, named pipe, file speciali, link simbolici)
 *	devono essere ignorati.
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

typedef struct inodeList {
	ino_t inode;
	struct inodeList* next;
}inodeList;

typedef inodeList* inodeList_ptr;

int isElementInList(inodeList* head, ino_t element) {
	printf("Element inode: %ld \n",element);
	if(head == NULL) {
		return 0;
	}else {
		inodeList* tmp = head;
		while (tmp!=NULL) {
			if (tmp->inode == element) {
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
	inodeList* head=NULL;
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

int main(int argc, char* argv[]) {
	char rootDir[PATH_MAX];
	if (argc > 1) {
		strcpy(rootDir, argv[1]);
		recursivelyDirectoryExploration(rootDir);
		printf("Number of files: %d\n", fileCounter);
		printf("Number of dir: %d\n", dirCounter);

	}else {
		getcwd(rootDir, sizeof(rootDir));
		recursivelyDirectoryExploration(rootDir);
		printf("Number of files: %d\n", fileCounter);
		printf("Number of dir: %d\n", dirCounter);
	}
}
