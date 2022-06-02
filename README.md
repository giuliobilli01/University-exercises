# University Exercises
Repository for the second year's exercises of CS course at the university of Bologna.

## SO

### Syscall 

* int eventfd(unsigned int initval, int flags): crea un eventfd object che può essere utilizzato per aspettare/notificare eventi. L'eventfd object contiene un unsigned int a 64 bit utilizzato come counter. Il counter viene inizializzato con il valore nel primo argomento. Come valore di ritorno, viene ritornato un file descriptor che può essere utilizzato per accedere all'eventfd object. Con la flag EFD_SEMAPHORE eventfd assume la semantica di un semaforo. Infatti se il suo counter ha un valore maggiore di 0, allora la funzione read ritorna il valore 1 e il counter viene decrementato di 1; se invece il counter è zero la chiamata di read provoca il blocco del processo finchè il counter non aumenta. La chiamata alla funzione write aggiunge l'intero da 8 byte(il buffer) al counter.

* int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg) : questa funzione crea un nuovo thread nel processo chiamante. Il nuovo thread iniza l'esecuzione con la l'esecuzione della funzione start_routine(arg). Il thread creato termina se chiama pthread_exit() che specifica l'exit status, il quale è disponibile in un altro thread dello stesso processo che chiama pthread_join(); oppure termina quando ritorna da start_routine() o se viene cancellato con pthread_cancel().


### Libraries and API

* inotify: fornisce metodi per monitorare directory e eventi nel filesystem in generale. Quando una directory viene monitorata inotify ritornerà gli eventi riguardanti quella directory.
Di seguito una procedura standard per l'inizializzazione di inotify su una directory(se si vogliono leggere più eventi inserire il while in un altro while (numberOfEvents = read(fd, buffer, EVENT_BUF_LEN)):
```C
#include <sys/inotify.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#define EVENT_SIZE (sizeof (struct inotify_event))
#define EVENT_BUF_LEN (1024 * ( EVENT_SIZE + 16))

int main(int argc, char*argv[]) {
  ...
  ...
  ...

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
    // Si può accedere ai campi dell'event per ricavare    informazioni utili
    struct inotify_event* event = (struct inotify_event*) &buffer[i];
    ...
    ...
    ...
    i += EVENT_SIZE + event->len;
  }
  inotify_rm_watch(fd, wd);
  close(fd);
  return 0;
}
```

### NOTE:

* I file collegati da un hard link hanno lo stesso inode, compreso il file originale 

* La syscall fork crea un processo figlio del chiamante e dopo la creazione entrambi i processi continuano a eseguire il codice sotto la chiamata.
  Se il valore ritornato dalla fork è 0 allora il controllo è passato al processo creato, se è -1 c'è stato un errore e se è > 0 è il pid del processo crato(viene ritornato al chiamante).

* Utilizzare lstat o stat per ricavare informazioni sul tipo di file. Il campo st_mode tramite funzioni o con & con constanti può essere utilizzato per trovare il tipo di file. 
ES
```C
// Controlliamo se il file è un eseguibile
struct stat file;
lstat(filePath, &file);
if (S_IXUSR & file.st_mode) {}
```

* dup2 può essere utilizzato per stampare l'output di un comando su un file. Esso prende un file descriptor che può essere creato tramite la funzione open().
ES:
```C
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
```
* Quando si elimina un file con rm se si ha un processo che lo mantiene aperto è possibile leggere e scrivere sul file, in quanto non viene liberato il file descriptor nel caso in cui un processo lo sta utilizzando.

* realpath() funziona se il nome del file da trovare è nella directory in cui è il processo che lo chiama, oppure bisogna mettergli il path per trovare il file.

* Per esplorare i file all'interno di una directory conviene usare readdir dopo aver eseguito opendir(DIR* dir). Poi con una struct dirent è possibile avere informazioni sui file all'interno della directory.
```C
#include <dirent.h>
#include <fcntl.h>


DIR* targetDir = opendir(dir);
struct dirent *entry;
file_t files[100];
if (targetDir == NULL){
	perror("Unable to read directory\n");
	exit(EXIT_FAILURE);
}
while ((entry=readdir(targetDir))) {
	if (entry->d_type & DT_REG) {
		char filePath[PATH_MAX];
		strcpy(filePath, dir);
		strcat(filePath, "/");
		strcat(filePath, entry->d_name);
		}
}

```
* Per compilare con eventuali librerie esterne come quella del prof conviene utilizzare:
```shell
gcc file.c -L/home/your_user/path_to_library/build -l:libexecs.a
```
## Web Tecnologies