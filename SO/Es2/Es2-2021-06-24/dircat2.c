/**
 * @file Es2-2021-06-24.c
 * @author your name (you@domain.com)
 * @brief Esercizio 2: Linguaggio C: 10 punti
completare dircat. Se il file aggiunto a D è un eseguibile dircat deve inserire in F dopo la riga di testata
l'output dell'esecuzione del nuovo file non già il suo contenuto. Completata l'esecuzione il file
eseguibile deve venir cancellato come nell'esercizio 1.
 * @version 0.1
 * @date 2022-05-27
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

int isExecutable(char* argument) {
  int i=0;
  while (argument[i] != '\0') {
    if (argument[i] == '.') {
      return 0;
    }
    i++;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  char dir[PATH_MAX];
  strcpy(dir, argv[1]);

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
  wd = inotify_add_watch(fd, dir, IN_CREATE | IN_MOVE);

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
    if ((event->mask & IN_CREATE) || (event->mask & IN_MOVE)) {
      if (!(event->mask & IN_ISDIR)) {
        FILE* destFile = fopen(argv[2], "a");

        char fileName[event->len];
        char filePath[PATH_MAX];
        strcpy(fileName, event->name);


        // Salviamo il path del file creato
        strcpy(filePath, dir);
        strcat(filePath, "/");
        strcat(filePath, fileName);

        // Controlliamo se il file inserito è un eseguibile
        if (isExecutable(fileName)) {
          fprintf(destFile, "File name: %s\n", fileName);
          // Utilizziamo dup2 per indirizzare l'output sul file
          char* argumentList[2];
          argumentList[0] = fileName;
          argumentList[1] = NULL;
          char command[PATH_MAX];
          strcpy(command, "./");
          strcat(command, fileName);

          fflush(destFile);
          int fd1 = fileno(destFile);
          pid_t child;
          int status;
          // esegue il file e scrive il risultato della 
          if ((child = fork()) == 0){
              dup2(fd1, 1);
              close(fd1);
              execvp(command, argumentList);
          }
          wait(&status); // wait for child process
          fprintf(destFile, "\n\n");
          //unlink(filePath);
          exit(EXIT_SUCCESS);
        }else {
        FILE* sourceFile = fopen(filePath, "r");
        fprintf(destFile, "File name: %s\n", fileName);
        char c;
        while ((c = fgetc(sourceFile)) != EOF) {
          fputc(c, destFile);
        }
        fprintf(destFile, "\n\n");
        fclose(destFile);
        fclose(sourceFile);
        //unlink(filePath);
        exit(EXIT_SUCCESS);
        }
      }
    }
    i+= EVENT_SIZE + event->len;

  } 
  inotify_rm_watch(fd, wd);
  close(fd);
  return 0;
}