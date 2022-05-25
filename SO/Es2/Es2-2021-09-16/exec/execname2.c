/**
 * @file execname2.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C: 10 punti
modificare il programma dell'esercizio 1 per fare in modo che execname2 scriva l'output
dell'esecuzione nel file invece che cancellarlo.
Nell'esempio precedente il programma execname2 non emette alcun output ma il comando
cat 'exec/echo ciao mare'
produce come risultato:
ciao mare
 * @version 0.1
 * @date 2022-05-25
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
#include <fcntl.h>

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
      if (event->mask & IN_ISDIR) {
        printf("A directory has been created");
      }
      else {

        // Salviamo il nome del file
        char fileName[event->len];
        char filePath[100];
        strcpy(fileName, event->name);

        // Salviamo il path del file create
        strcpy(filePath, dir);
        strcat(filePath, "/");
        strcat(filePath, fileName);

        char* p= &fileName[0];
        //int spaces = countSpaces(p);
        int spaces = 3;
        char* argumentList[spaces + 1];

        char* token = strtok(fileName, " ");
        char* command = token;
        int k = 0;
        while (token != NULL && k < spaces) {
          argumentList[k] = token;
          token = strtok(NULL, " ");
          k++;
        }
        argumentList[k] = NULL;
        char* prova[] = {"ls", "-l", NULL};
        pid_t child;
        if ((child = fork()) == 0) {
          int fdOut = open(filePath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
          dup2(fdOut, 1);
          close(fdOut);
          int status= execvp(command, argumentList);
          
          if (status == -1) printf("errore");
        }

        wait(&child);
      }
    }
    i += EVENT_SIZE + event->len;
  }
  inotify_rm_watch(fd, wd);
  close(fd);

  return 0;
}