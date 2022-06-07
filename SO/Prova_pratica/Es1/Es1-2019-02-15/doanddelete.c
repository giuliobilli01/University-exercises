/**
 * @file doanddelete.c
 * @author your name (you@domain.com)
 * @brief Usando il servizio inotify(7) scrivere il programma doandelete.
Questo programma viene attivato con un unico parametro che deve essere una directory vuota
(controllare la coerenza del parametro!).
Quando viene aggiunto un file alla directory questo viene eseguito e cancellato.
 * @version 0.1
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <sys/inotify.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>

#define EVENT_SIZE (sizeof (struct inotify_event))

// The behavior when the buffer given to read(2) is too small to
//       return information about the next event depends on the kernel
//       version: in kernels before 2.6.21, read(2) returns 0; since
//       kernel 2.6.21, read(2) fails with the error EINVAL.  Specifying a
//       buffer of size
//
//           sizeof(struct inotify_event) + NAME_MAX + 1
//
//       will be sufficient to read at least one event.
#define EVENT_BUF_LEN (1024 * ( EVENT_SIZE + 16))

int main(int argc, char*argv[]) {
  if (argc < 2) {
    printf("Error: Invalid number of arguments\n");
    exit(EXIT_FAILURE);
  }
  char dir[PATH_MAX];
  strcpy(dir, argv[1]);

  // Controlliamo se la directory esiste
  DIR* checkDir = opendir(dir);
  if (checkDir == NULL) {
    printf("Error: directory \"%s\" does not exist\n", dir);
    exit(EXIT_FAILURE);
  }

  //  ed è vuota
  struct dirent *d;
  int n=0;
  while ((d = readdir(checkDir)) != NULL) {
    if (n > 2){
      printf("Error: directory isn't empty\n");
      exit(EXIT_FAILURE);
    }
  }

  // Inizializziamo inotify

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
  wd = inotify_add_watch(fd, dir, IN_CREATE | IN_MOVE) ;

  // Chiamiamo read che rimane bloccato finchè non si verificano degli eventi 
  numberOfEvents = read(fd, buffer, EVENT_BUF_LEN);

  // Controlliamo se si sono verificati errori
  if (numberOfEvents < 0) perror("read");

  int i=0;
  while (i < numberOfEvents) {
    struct inotify_event* event = (struct inotify_event*) &buffer[i];
    if (event->mask & IN_CREATE | IN_MOVE) {
      if (!(event->mask & IN_ISDIR)) {
        // Nel caso sia stato aggiunto un file
        // Prendiamo il path del file creato
        char filePath[PATH_MAX];
        strcpy(filePath, dir);
        strcat(filePath, "/");
        strcat(filePath, event->name);
        
        // Controlliamo se il file è un eseguibile
        struct stat file;
        stat(filePath, &file);

        if ((S_IXUSR & file.st_mode)) {
          char command[150];
          char*args[2];
          // Se si esegue con il path non serve il ./
          //strcpy(command, ".");
          strcat(command, dir);
          strcat(command, "/");
          strcat(command, event->name);
          args[0] = command;
          args[1] = NULL;
          // Eseguiamo il file
          pid_t child;
          if ((child = fork()) == 0) {
            printf("command: %s\n", command);
            printf("args: %s\n", args[0]);
            int status= execvp(command, args);
            if (status == -1) printf("errore");
          }
          wait(&child);
          // Eliminiamo il file
          //unlink(filePath);
        } else {
          printf("Error: file not executable\n");
          exit(EXIT_FAILURE);
        }

      }
    }
    i += EVENT_SIZE + event->len;
  } 
  inotify_rm_watch(fd, wd);
  close(fd);
  return 0;
}

 

  




