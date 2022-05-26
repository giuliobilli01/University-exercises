/**
 * @file dircat.c
 * @author your name (you@domain.com)
 * @brief Esercizio 1: Linguaggio C (obbligatorio) 20 punti.
Usando il metodo inotify implementare il programma dircat.
dircat ha 2 parametri: il pathname di una directory (vuota) D e di un file F.
Ogni volta che un file viene messo in D il programma dircat aggiunge a F una riga di testata
contenente il nome del file e ne copia il contenuto in F. Finita la copia il file che era stato messo in D
viene cancellato (la directory D torna vuota).
(per fare gli esperimenti si consiglia di preparare i file di prova in un'altra directory e copiarli in D)
 * @version 0.1
 * @date 2022-05-26
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

int main(int argc, char*argv[]) {
  char dir[PATH_MAX];
  strcpy(dir, argv[1]);
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
    if ((event->mask & IN_CREATE) || (event->mask & IN_MOVE)) {
      if (!(event->mask & IN_ISDIR)) {
        FILE* destFile = fopen(argv[2], "a");

        char fileName[event->len];
        char filePath[PATH_MAX];
        strcpy(fileName, event->name);

        // Salviamo il path del file create
        strcpy(filePath, dir);
        strcat(filePath, "/");
        strcat(filePath, fileName);

        FILE* sourceFile = fopen(filePath, "r");
        fprintf(destFile, "File name: %s\n", fileName);
        char c;
        while ((c = fgetc(sourceFile)) != EOF) {
          fputc(c, destFile);
        }
        fprintf(destFile, "\n\n");
        fclose(destFile);
        fclose(sourceFile);
        unlink(filePath);

      }
    }
    i+= EVENT_SIZE + event->len;
  }
  inotify_rm_watch(fd, wd);
  close(fd);
  return 0;
}