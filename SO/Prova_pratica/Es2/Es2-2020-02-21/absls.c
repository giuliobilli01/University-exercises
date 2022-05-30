/**
 * @file absls.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C: 10 punti
Scrivere il comando absls che mostri per ogni file della directory passata come parametro il path
completo di ogni file (mostrando al posto dei link simbolici il path completo dei file puntati).
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char*argv[]) {

  DIR* directory;
  directory = opendir(argv[1]);
  struct dirent* entry;
  if (directory == NULL) {
    printf("Error: opendir() failed\n");
    exit(EXIT_FAILURE);
  }
  while( (entry = readdir(directory)) != NULL) {
    char*p = NULL;
    char filePath[PATH_MAX];
    p= realpath(entry->d_name, filePath);
    if (p != NULL) {
      printf("%s\n", filePath);
    }

  }

  return 0;
}