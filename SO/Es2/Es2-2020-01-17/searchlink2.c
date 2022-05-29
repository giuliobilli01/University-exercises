/**
 * @file searchlink.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Estendere il programma precedente in modo che accetti le seguenti opzioni:
-c copia il file originale al posto di tutti i link
-l trasforma tutti i link in link fisici
-s trasforma tutti i link in link simbolici
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
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
#include <libgen.h>

void recursivelyDirecotryExploration(char* targetFile, char* directory, int option) {
  // Apriamo la directory in input 
  DIR* dir = opendir(directory);
  if (dir == NULL) {
    printf("Error: unable to open directory \"%s\"\n", directory);
    exit(EXIT_FAILURE);
  }

  // Se arriva qua la directory è stata aperta correttamente
  struct dirent *entry;
  
  while ((entry = readdir(dir)) != NULL) {
    char newDir[PATH_MAX];
    // Per ogni entry devo controllare se è un hard link o un soft link
    // e nel caso stampare. Se invece è una directory devo entrarci 
    // e continuare la ricerca
    if ( entry->d_type & DT_DIR) {
      strcpy(newDir, directory);
      strcat(newDir, "/");
      strcat(newDir, entry->d_name);
      if (!(strcmp(entry->d_name, "..")==0) && !(strcmp(entry->d_name, ".")==0)) {
        recursivelyDirecotryExploration(targetFile, newDir, option);
      }
    }else {
      char entryPath[PATH_MAX];
      char inputFilePath[PATH_MAX];
      struct stat file;

      // Creiamo il path del file che stiamo leggendo
      strcpy(entryPath, directory);
      strcat(entryPath, "/");
      strcat(entryPath, entry->d_name);

      // Otteniamo i dati del file
      lstat(entryPath, &file);

      // Nel caso in cui il file sia un symbolic link
      if (S_ISLNK(file.st_mode)) {
          char linkDestination[PATH_MAX];
          // Troviamo il path del link file
          realpath(entryPath, linkDestination);
          realpath(targetFile, inputFilePath);
          // E lo compariamo con quello del file obbiettivo
          if (strcmp(linkDestination, inputFilePath) == 0) {
            if (option == 0) {
            printf("symlink %s\n",entryPath);
            }
            if (option == 1) {
              // Elimino il link file
              unlink(entryPath);
              // Estraggo il nome del file dal path in input
              char newFilePath[PATH_MAX];
              char filePathCpy[PATH_MAX];
              strcpy(filePathCpy, targetFile);
              strcpy(newFilePath, directory);
              strcat(newFilePath, "/");
              strcat(newFilePath, basename(filePathCpy));
              FILE* srcFile = fopen(targetFile, "r");
              FILE* destFile = fopen(newFilePath, "a");
              char c;
              while ((c = fgetc(srcFile)) != EOF) {
                fputc(c, destFile);
              }
              fclose(destFile);
              fclose(srcFile);
            }
            if (option == 2) {
              char linkPath[strlen(entryPath)];
              char linkName[PATH_MAX];
              strcpy(linkName, entryPath);
              realpath(targetFile, linkPath);
              unlink(entryPath);
              printf("%s\n", linkPath);
              printf("%s\n", linkName);
              int res = link(linkPath, linkName);
              if (res != 0) {
                printf("Error durint link creation");
              }
            }
          }
      // Nel caso in cui il file non sia un symbolic link
    } else if(S_ISREG(file.st_mode)) {
        // Confrontiamo gli inode del file obbiettivo 
        // e del file nella directory per vedere se 
        // sono fanno riferimento allo stesso file
        realpath(targetFile, inputFilePath);
        struct stat targetFileDescription;
        lstat(inputFilePath, &targetFileDescription);
        if ((file.st_ino == targetFileDescription.st_ino) && (strcmp(entryPath, targetFile) != 0)) {
          if (option == 0)
            printf("link %s\n", entryPath);

           if (option == 3) {
            char linkName[PATH_MAX];
            strcpy(linkName, entryPath);
            printf("%s\n", entryPath);
            unlink(entryPath);
            int res = symlink(targetFile, linkName);
            if (res != 0) {
              printf("Error during link creation");
            }
          }
        }
      }
    }
  }
}

int main(int argc, char*argv[]) {
  char rootDir[PATH_MAX];
  char targetFile[PATH_MAX];
  int option=0;
  // Salviamo il path della directory e del file in input
  strcpy(targetFile, argv[1]);
  strcpy(rootDir, argv[2]);
  if (argc > 3) {
    if (strcmp(argv[3], "-c") == 0) option = 1;
    if (strcmp(argv[3], "-l") == 0) option = 2;
    if (strcmp(argv[3], "-s") == 0) option = 3;
  }
  // Controlliamo ricorsivamente il sottoalbero
  recursivelyDirecotryExploration(targetFile, rootDir, option);

  return 0;
}