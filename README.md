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

* inotify: fornisce metodi per monitorare direcotory e eventi nel filesystem in generale. Quando una directory viene monitorata inotify ritornerà gli eventi riguardanti quella directory.
Di seguito una procedura standard per l'inizializzazione di inotify su una directory:
```C
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
}
```

### NOTE:

* I file collegati da un hard link hanno lo stesso inode, compreso il file originale 

* La syscall fork crea un processo figlio del chiamante e dopo la creazione entrambi i processi continuano a eseguire il codice sotto la chiamata.
  Se il valore ritornato dalla fork è 0 allora il controllo è passato al processo creato, se è -1 c'è stato un errore e se è > 0 è il pid del processo crato(viene ritornato al chiamante).


## Web Tecnologies