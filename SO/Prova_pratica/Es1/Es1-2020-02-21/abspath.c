/**
 * @file abspath.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Il comando abslink, da implementare, deve sostituire un link simbolico con uno equivalente che sia
un riferimento ad un path assoluto.
Ad esempio: se mylink e' nella directory /home/user e punta a myfile, 'abspath mylink" deve sostituire
mylink con un symbolic link a /home/user/myfile.
Hint: considerate l'uso della funzione realpath.
 * @version 0.1
 * @date 2022-05-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


int main(int argc, char* argv[]) {

  if (argc < 2) {
    printf("Error: Invalid number of arguments");
  } else{
    char link[PATH_MAX];
    char realPath[PATH_MAX];
    ssize_t output = readlink(argv[1], link, sizeof(link));
    if (output < 0) {
      printf("Error during link processing");
    }
    realpath(link, realPath);
    unlink(argv[1]);
    symlink(realPath, argv[1]);

    printf("%s", realPath);
  }
  
  return 0;
}