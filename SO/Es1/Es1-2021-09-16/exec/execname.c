/**
 * @file execname.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti
Creare una directory chiamata exec. Scrivere un programma execname che se viene aggiunto un file
nela directory exec interpreti il nome del file come comando con parametri, lo esegua e cancelli il file.
es: sopo aver lanciato execname:
execname exec
a seguito di questo comando:
touch 'exec/echo ciao mare'
il programma stampa:
ciao mare
(consiglio, usare inotify)
 * @version 0.1
 * @date 2022-05-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (1024 * ( EVENT_SIZE + 16))

int countSpaces(char* arrStart) {
  int spaces=0;
  int i=0;
  while (arrStart[i] != '\0') {
    if (arrStart[i] == ' ') spaces++;
    i++;
  }
  return spaces;
}

int main(int argc, char *argv[]) {
  
  char dir[PATH_MAX];
  getcwd(dir, sizeof(dir));

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
  wd = inotify_add_watch(fd, dir, IN_CREATE);

  // Chiamiamo read che rimane bloccato finchè non si verificano degli eventi 
  numberOfEvents = read(fd, buffer, EVENT_BUF_LEN);

  // Controlliamo se si sono verificati errori
  if (numberOfEvents < 0) perror("read");

  // A questo punto se non ci sono stati errori numberOfEvents 
  // tiene il conto degli eventi avvenuti
  // e il buffer contiene gli eventi 
  int i=0;
  while (i < numberOfEvents) {
    struct inotify_event* event = (struct inotify_event*) &buffer[i];
    if (event->mask & IN_CREATE) {
      if (!(event->mask & IN_ISDIR)) {
        // Salviamo il nome del file
        char fileName[event->len];
        char filePath[PATH_MAX];
        strcpy(fileName, event->name);

        // Salviamo il path del file create
        strcpy(filePath, dir);
        strcat(filePath, "/");
        strcat(filePath, fileName);

        char* p= &fileName[0];
        int spaces = countSpaces(p);

        char* argumentList[spaces + 1];

        char* token = strtok(fileName, " ");
        char* command = token;
        int k = 0;
        while (token != NULL && k < spaces) {
          argumentList[k] = token;
          token = strtok(NULL, " ");
          k++;
        }
        
        //printf("%s, %s, %s ", argumentList[0], argumentList[1], argumentList[2]);
        pid_t child = fork();
        if (child == 0) {
          execvp(command, argumentList);
        }

        wait(&child);
        unlink(filePath);
      }
    }
    i += EVENT_SIZE + event->len;
  }
  inotify_rm_watch(fd, wd);
  close(fd);

  return 0;
}