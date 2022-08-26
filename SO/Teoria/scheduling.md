# Scheduling

## Introduzione
Il sistema operativo deve gestire le risorse e per farlo ha bisogno di doverse strutture dati per mantenere informazioni sulle risorse gestite.
Queste strutture comprendono:

* Tabelle di memoria: utilizzate per allocare memoria per il SO, per i processi e mantengono informazioni sui meccanismi di protezione

* Tabelle di I/O: gestione di code di richieste e informazioni sullo stato di assegnazione dei dispositivi

* Tabelle del file sysstem: elenco dei dispositivi utilizzati per mantenere il file system e elenco dei file aperti e del loro stato

* Tabelle dei processi: contiene i descrittori dei processi (PCB).

## Descrittori dei processi
La manifestazione fisica di un processo è rappresentata dal descrittore di un processo(PCB), il quale contiene:

* Il codice del processo

* I dati su cui operare

* Uno stack di lavoro per la gestione delle chiamate di funzione 

* Un insieme di dati aggiuntivi che contengono informazioni per la gestione del processo

## PCB
I dati all'interno di un PCB si possono dividere in 3 parti:

* Informazioni di identificazione del processo: 
  
  * identificatore del processo (pid, id) che può essere in indice all'interno della tabella dei processi o un valore incrementale.
  
  * identificatori di altri processi legati al processo: pid del processo padre o altri

  * id dell'utente che ha richiesto l'esecuzione del processo

* Informazioni di stato del processo:
  
  * registri di stato del processore

  * registri speciali come il PC e i registri di stato 

* Inoformazioni di controllo del processo:

  * informazioni di scheduling:
    
    * stato: pronto, in attesa, in esecuzione

    * scheduling: priorità, puntatori per gestione di code ecc

    * identificatore dell'evento per cui il processo è in attesa 

    * informazioni di gestione della memoria: configurazione MMU e puntatori alle tabelle delle pagine

    * informazioni di accounting: tempo di esecuzione del processo e tempo trascorso dall'attivazione del processo

    * informazioni sulle risorse: risorse controllate dal processo come file, device ecc

    * informazioni per Inter Process Communication (IPC): stato dei segnali, semafori ecc

## Scheduler
E' la componente principale del kernel, esso gestisce l'avvicendamento dei processi, scegliendo quale deve andare in esecuzione.
Lo schedule è la sequenza temporale di assegnazione delle risorse, ai richiedenti, lo scheduling è l'azione di calcolare uno schedule e lo scheduler è la componente software che calcola lo schedule.

### Precisazioni

* Lo short term scheduler seleziona quale dei processi in stato ready deve essere eseguito, ovvero a quale dare il controllo della CPU.(di solito si fa riferimento a questo)

* Il long-term scheduler invece viene utilizzato nei sistemi batch e seleziona quali processi creare fra quelli che non hanno ancora iniziato la loro esecuzione.


## Processi e thread
I processi multithread sono processi in cui esistono diverse linee di controllo, ognuna delle quali può eseguire un insieme diverso di istruzioni. 
Ogni thread possiede la propria copia dello stato del processore, il proprio program counter e uno stack separato. I thread che appartengono allo stesso processo condividono il codice, i dati e le risorse di I/O. Quindi i thread associati allo stesso processo condividono lo spazio di memoria e le risorse rendendo più semplice la creazione di applicazioni. Inoltre i thread sono molto più efficenti in quanto la creazione di un thread è motlo meno costosa rispetto a creare un nuovo processo e anche il context switching tra thread è meno costoso. Un sistema operativo può creare thread in due modi: user thread e kernel thread

### User Thread
Gli user thread vengono supportati sopra il kernel e vengono implementati da una libreria a livello utente che fornisce supporto senza far intervenire il kernel. Se il kernel è single threaded qualsiasi user thread che effettua una chiamata di sistema bloccante prova il blocco dell'intero processo.

### Kernel thread
I kernel thread sono implementati a livello kernel e supportati direttamente dal SO. Essendo gestiti direttamente dal kernel se un thread esegue un'operazione bloccante il kernel può selezionare un altro thread in attesa. E' un implementazione più lenta in quanto è necessario passare in kernel mode

## Multithreading
Esistono anche modelli multithreading che supportano sia kernel thread che user thread, in particolare esistono tre modelli:
  
  * Many-to-One: più user thread vengono mappati su un solo kernel-thread. Quindi solo un thread alla volta può accedere al kernel e quindi solo una entità schedulabile viene vista dal SO. Di conseguenza questo modello limita la concorrenza e non sfrutta il multiprocessore.

  * One-to-one: ogni user thread viene associato a un kernel-thread. Quindi tutti i thread possono accedere al kernel contemporaneamente. Il limite principale di questo modello è che ogni thread aggiuntivo aggiunge peso al processo costringendo così la creazione di un limite al numero di thread.

  * Many.to-many: elimina le limitazioni del one to-one e estende le capacità di multithreading. In questo modello una libreria user-thread fornisce un sofisticato scheduling degli user-thread sui kernel-thread. Il kernel deve gestire solo i thread che sono effettivamente attivi.

## Scheduling
Per rappresentare uno schedule si utilizza il diagramma di Gantt. Esso indica l'utillizzo della CPU nel tempo da parte dei processi. Nel caso si debba rapprensentare l'utilizzo di più risorse il diagramma avrà più righe.

### Tipi di scheduler
Uno scheduler si dice non preemptive o cooperativo se i context switch avvengono solo quando in processo termina oppure passa da stato running a waiting(a causa di una syscall bloccante). Ha come vantaggio il fatto che non sono necessari meccanismi hardware come timer ma gestisce peggio le risorse

Uno scheduler si dice preemptive se i context switch possono avvenire in ogni situazione, quindi anche nel caso in cui un porcesso passa da running a ready (interrupt) oppure da waiting a ready. Permette un utilizzo migliore delle risorse.

### CPU bound e I/O bound
* Si definiscono CPU bound in informatica i processi che sfruttano pesantemente le risorse computazionali del processore, ma non richiedono servizi di ingresso/uscita dati al sistema operativo in quantità rilevanti. È in contrapposizione a I/O bound. 

* In informatica, I/O bound si riferisce alla condizione in cui il tempo necessario a compiere un'elaborazione è determinato principalmente dall'attesa delle operazioni di input/output. Ciò si contrappone ai processi CPU bound. Questa circostanza si verifica quando i dati vengono richiesti ad una velocità minore di quella a cui sono "consumati", o, in altre parole, si spende più tempo a richiedere i dati che ad elaborarli[1]. 

### Algoritmi di scheduling

#### First come, First served
Il processo che arriva per primo viene servito per primo, (politica senza preemption). Si implementa attraverso una coda con politica FIFO. Questo approccio ha elevati tempi di attesa e di turnaround e i processi CPU burst ritardano i processi I/O bound, fino ad arrivare in casi di ready queue vuota a causa dell'attesa.

### Shortest Job First
La CPU viene assegnata al processo ready con il CPU burst successivo minimo. (politica senza preemption). Questo algoritmo è ottimale per il tempo di attesa in quanto permette di raggungere il minimo tempo di attesa, il problema è che non si può realizzare in pratica ma si possono fare solo delle approsimazioni.(può causare starvation). Questo algoritmo si può eseguire sia in forma non preemptive dove il processo esegue fino al completamento del suo CPU burst, sia in forma preemptive dove il processo può essere messo nella coda ready se arriva un processo con un CPU burst più breve di quello rimanente al processo corrente.

### Round robin





