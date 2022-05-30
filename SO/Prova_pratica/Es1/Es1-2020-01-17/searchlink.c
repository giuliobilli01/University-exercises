/**
 * @file searchlink.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Scrivere un programma searchlink che dati due parametri (nell'ordine un file f ed una directory d)
metta in output l'elenco dei path all'interno dell'albero che ha radice in d che fanno riferimento ad f
o come link fisico o come link simbolico.
es:
searchlink myfile mydir
link a
link d/b
symlink e/s
significa che dir/a e dir/d/b si riferisono a f come link fisici mentre dir/e/s e' un link simbolico che punta
ad f
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

void recursivelyDirecotryExploration(char* targetFile, char* directory) {
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
        recursivelyDirecotryExploration(targetFile, newDir);
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
          printf("symlink %s\n",entryPath);
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
          printf("link %s\n", entryPath);
        }
      }
    }
  }
}

int main(int argc, char*argv[]) {
  char rootDir[PATH_MAX];
  char targetFile[PATH_MAX];

  // Salviamo il path della directory e del file in input
  strcpy(targetFile, argv[1]);
  strcpy(rootDir, argv[2]);
  // Controlliamo ricorsivamente il sottoalbero
  recursivelyDirecotryExploration(targetFile, rootDir);

  return 0;
}