# University Exercises
Repository for the second year's exercises of CS course at the university of Bologna.

* [University Exercises](#university-exercises)
   * [SO](#so)
      * [Argomenti trattati negli esercizi](#argomenti-trattati-negli-esercizi)
      * [Headers](#headers)
      * [Syscall](#syscall)
      * [Libraries and API](#libraries-and-api)
      * [Snippets:](#snippets)
      * [Script](#script)
         * [Python](#python)
         * [Bash](#bash)
      * [NOTE:](#note)
   * [Web Tecnologies](#web-tecnologies)


## SO

### Argomenti trattati negli esercizi
* Es1-2021-09-16: Utilizzo di inotify, utilizzo di execvp per eseguire comandi con conseguente utilizzo di fork.
```Text
Creare una directory chiamata exec. Scrivere un programma execname che se viene aggiunto un file
nela directory exec interpreti il nome del file come comando con parametri, lo esegua e cancelli il file.
es: sopo aver lanciato execname:
execname exec
a seguito di questo comando:
touch 'exec/echo ciao mare'
il programma stampa:
ciao mare
(consiglio, usare inotify)
```

* Es2-2021-09-16: modificare Es1, scrivendo sul file, utilizzo dup2 per reindirizzare l'output.
```Text
modificare il programma dell'esercizio 1 per fare in modo che execname2 scriva l'output
dell'esecuzione nel file invece che cancellarlo.
Nell'esempio precedente il programma execname2 non emette alcun output ma il comando
cat 'exec/echo ciao mare'
produce come risultato:
ciao mare
```
* Es3-2021-09-16: lista dei file in ordine alfabetico, utilizzo di dictionary, os walk.
```Text
Scrivere un programma/script che faccia la lista riscorsiva dei file in un sottoalbero riportando in
# ordine alfabetico per nome di file in quale/quali sottodirectory compare.
# e.g.
# rlsr mydir
# ciao: . ./a
# mare: ./a ./b
# sole: .
```
* Es1-2021-07-15: Utilizzo dlopen e dlsym
```Text
Sia dato questo programma hw.c (vi viene fornito in /public/hw.c)
#include <stdio.h>
int main(int argc, char*argv[]) {
printf("hello world:");
for(argv++, argv--; argc > 0; argv++, argc--)
printf(" %s",*argv);
printf("\n");
return 0;
}
Il programma hw.c può essere compilato come libreria dinamica:
gcc --shared -o hw.so hw.c
La libreria dinamica non è un eseguibile
$ ./hw.so 1 2 3 4
Segmentation fault
ma può essere caricata a tempo di esecuzione tramite dlopen. Scrivere un programma "lancia" in
grado di eseguire il codice di hw.so
$ ./lancia hw.so 1 2 3 4
hello world: hw.so 1 2 3 4
(suggerimenti: dlopen non cerca nella directory corrente, occorre passare il path assoluto della libreria.
"main" in hw.so è una normale funzione: occorre cercare l'indirizzo della funzione main nella libreria
ed invocarla,)
```
* Es2-2021-07-15: Utilizzo dlopen e dlsym con riconoscimento la libreria e eseguibile(nel caso di eseguibile va usato execvp e fork)
```Text
 Estendere l'esercizio 1. Il nuovo programma autolancia deve riconoscere se il primo parametro è una
libreria dinamica o un eseguibile gestendo entrambi i casi:
gcc -o hw hw.c
$ ./autolancia hw.so 1 2 3 4
hello world: hw.so 1 2 3 4
$ ./autolancia hw 1 2 3 4
hello world: hw.so 1 2 3 4

```
* Es3-2021-07-15 Python: Utilizzo di os.walk, di getmtime, setdefault con dictionary e sorted.
```Text
Scrivere uno script in grado si cercare all'interno di un sottoalbero del file system il file modificato più
di recente e quello la cui ultima modifica è avvenuta più anticamente.

```
* Es1-2021-06-24: Utilizzo di inotify e scrittura su un'altro file con fopen
```Text
Usando il metodo inotify implementare il programma dircat.
dircat ha 2 parametri: il pathname di una directory (vuota) D e di un file F.
Ogni volta che un file viene messo in D il programma dircat aggiunge a F una riga di testata
contenente il nome del file e ne copia il contenuto in F. Finita la copia il file che era stato messo in D
viene cancellato (la directory D torna vuota).
(per fare gli esperimenti si consiglia di preparare i file di prova in un'altra directory e copiarli in D)
```
* Es2-2021-06-24: Utilizzo inotify come prime e dup2 per indirizzare l'output sul file nel caso sia un eseguibile.
```Text
completare dircat. Se il file aggiunto a D è un eseguibile dircat deve inserire in F dopo la riga di testata
l'output dell'esecuzione del nuovo file non già il suo contenuto. Completata l'esecuzione il file
eseguibile deve venir cancellato come nell'esercizio 1.
```
* Es3-2021-06-24 Bash:  utilizzo di find e echo per identare file.c
```Text
Scrivere uno script o un programma python che corregga l'indentazione di tutti i file .c e .h presenti
# nel sottoalbero della directory passata come parametro (la working directory se non vi sono
# parametri).
# Hint: il comando:
# ex -n '+norm!gg=G' +wq prog.c
# corregge l'indentazione del programma sorgente C prog.c.
```
* Es1-2020-02-21: Utilizzo di readlink, symlink per creare un link simbolico e realpath per ottenere il path completo.
```Text
Il comando abslink, da implementare, deve sostituire un link simbolico con uno equivalente che sia
un riferimento ad un path assoluto.
Ad esempio: se mylink e' nella directory /home/user e punta a myfile, 'abspath mylink" deve sostituire
mylink con un symbolic link a /home/user/myfile.
Hint: considerate l'uso della funzione realpath.
```

* Es2-2020-02-21: Utilizzo di opendir e readdir per esplorare una directory
```Text
Scrivere il comando absls che mostri per ogni file della directory passata come parametro il path
completo di ogni file (mostrando al posto dei link simbolici il path completo dei file puntati)
```
* Es3-2020-02-21: Utilizzo di un dizionario di listdir, di splitext e di sorted.
```Text
Scrivere un programma python o uno script bash che produca il listato del contenuto di una directory
# in ordine di suffisso.
```
* Es1-2020-01-17: Esplorazione ricorsiva del sottoalbero, stat e lstat, realpath
```Text
Scrivere un programma searchlink che dati due parametri (nell'ordine un file f ed una directory d)
metta in output l'elenco dei path all'interno dell'albero che ha radice in d che fanno riferimento ad f
o come link fisico o come link simbolico.
es:
searchlink myfile mydir
link a
link d/b
symlink e/s
significa che dir/a e dir/d/b si riferisono a f come link fisici mentre dir/e/s e' un link simbolico che punta
ad f
```
* Es2-2020-01-17: Visita ricorsiva del sottoalbero, copia di file al posto dei link, sostituzione link fisici e linnk simbolici, lstat.
```Text
Estendere il programma precedente in modo che accetti le seguenti opzioni:
-c copia il file originale al posto di tutti i link
-l trasforma tutti i link in link fisici
-s trasforma tutti i link in link simbolici
```
* Es3-2020-01-17 Bash: Presa di tutti gli argomenti in input da terminale e creazione stringa in output
```Text
Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi
# para.py sleep 20 // ls -l // ps // sleep 3
# para.sh sleep 20 // ls -l // ps // sleep 3
# deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
```
* Es1-2019-09-18: Lancio di processi in parallelo, utilizzo di fork e wait(si ricorda che i processi generati con fork eseguono in modo concorrentemente)
 ```Text
 scrivere un programma para per lanciare parallelamente comandi
para sleep 20 // ls -l // ps // sleep 3
deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti
 ```
* Es2-2019-09-18: Lancio di processi in parallelo con un limite massimo di processi attivi, utilizzo di fork e wait(si ricorda che i processi generati con fork eseguono in modo.
 ```Text
 estendere para a paran che ha un parametro che indica il numero massimo di esecuzioni concorrenti:
paran 3 sleep 20 // ls -l // ps // sleep 3
al max esegue 3 comandi in parallelo, quindi esegue i primi 3 comandi, qundo uno fra essi termina
ne attiva un successivo e cosi' via.
 ```
* Es3-2019-09-18: Utilizzo di os.walk e di os.scandir per trovare i link fisici attraverso lo stesso inode.
```Text
Scrivere un programma python o uno script bash che faccia l'elenco dei pathname in un sottoalbero
che sono link fisici fra loro:
e.g.
searchln mydir
mydir/a mydir/d/b mydir/qq
mydir/uno mydir/due
significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file, cosi' come mydir/uno
mydir/due indicano uno stesso file (diverso dal precedente).
Nel sottoalbero possono esserci molteplici altri file, se hanno un solo nome non vengono indicati
nell'output.
```

* Es1-2019-07-16: manca

* Es3-2019-07-17: Utilizo di listdir, os.path.isfile per controllare se è un file, filecmp.cmp per comparare il contenuto dei file.
```Text
Scrivere un programma python o uno script bash che cerchi tutti i file con uguale contenuto in una
# directory. I file con lo stesso contenuto devono diventare link fisici a un unico file.
```
* Es1-2019-06-19: Utilizzo di prctl con PR_SET_CHILD_SUBREAPER per cambiare il processo a cui va l'exit status di un porcesso figlio che termina.
```Text
Normalmente se un processo è orfano l'exit status viene ricevuto da init o systemd (processo 1).
Usando l'opzione PR_SET_CHILD_SUBREAPER della system call prctl(2) è possibile cambiare questo
comportamento.
Scrivere un programma che crei un processo figlio e uno nipote (tramite fork). Fare in modo che
termini prima il figlo e poi il nipote.
Il programma deve mostrare che con prctl/PR_SET_CHILD_SUBREAPER la terminazione del nipote
viene rilevata dal nonno.
```
* Es2-2019-06-19: Utilizzo di prctl con PR_SET_NAME che cambia il nome con cui vengono visti i processi in esecuzione.
```Text
Tramite l'opzione PR_SET_NAME sempre di prctl fare in modo che con il comando "ps -Leo pid,comm"
i nomi dei tre rpocessi creati dall'esercizio 1 compaiano con nome "nonno","figlio" e "nipote".
```
* Es3-2019-06-19 Python: Utilizzo di os.walk, os.splitext per esplorare un sottoalbero e contare le righe dei file tramite file.read e (str).split per separare le righe.
```Text
Scrivere un programma python o uno script bash che calcoli il numero di righe presenti in tutti i file .c,
 .h, e Makefile (o makefile).
 Prima deve stampare ogni per ogni file .c il numero di righe, poi il totale righe per tutti i file .c,
 similmente per i file .h e i makefile e alla fine il totale generale;
 e.g.
 primo.c 100
 secondo.c 150
 dir/terzo.c 120
 tot .c 370
 primo.h 10
 dir/terzo.h 24
 tot .h 34
 Makefile 44
 dir/makefile 22
 tot Makefile 66
 tot source 470 
```
* Es1-2019-05-29: Utilizzo di pthread_create per creare thread che eseguono processi separati, pthread_join per aspettare la terminazione del thread in input e utilizzo di eventfd per creare semafori.
```Text
Usando pthread_create occorre creare due thread che chiameremo produttore e consumatore.
Il thread produttore ripetutamente genera un numero causuale, lo stampa lo mette in una variabile
condivisa con il consumatore e attende (ritardo casuale). Il thread consumatore legge dalla variabile
condivisa i valori e li stampa (anche il consumatore attende per un periodo casuale prima di tentare di
leggere il valore successivo)
Ogni valore prodotto deve venir consumato una e una sola volta, per la sincronizzazione si richiede di
usare eventfd in modalità EFD_SEMAPHORE.
```
* Es2-2019-05-29: shell minimale con libreria del prof, utilizzo di s2argv per ottenere un array di puntatori a stringhe per execvp. Utilizzo di fork e execvp.
```C
Scrivere una shell minimale usando la libreria s2argv/execs (da scaricare da github).
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input
```
* Es3-2019-05-29 Bash: Estrazione informazioni da file /proc/pid/status. Utilizzo di awk per per estrapolare elementi dalle righe, sed per eliminare elementi dalle righe. Utilizzo di cat per prendere il contenuto di un file, aek per prendere solo una colonna  e per eliminare le righe duplicate.
```Text
I file /proc/*/status contengono importanti informazioni relative ai processi in esecuzione.
In particolare una riga contiene la costante "Uid:" seguita da quattro numeri (sono l'uid reale, effettivo, salvato e del
 file system per il processo in considerazione).
Scrivere un programma python o uno script bash che per ogni utente che ha un ruolo in almeno un processo
 indichi quanti processi sono attivi che hanno quell'utente come reale, effettivo, salvato o del file system.
 esempio di output:
 0 10 12 12 12
 1000 5 3 3 3
 (l'utente 0 ha 10 processi come utente reale, 12 come effettivo, salvato e del file system. l'utente 1000 ha 5
 processi come utente reale e 3 come effettivo, salvato e del file system. Per esempio questo caso si riferirebbe a
 10 processi di root, 5 dell'utente 1000 dei quali 2 sono setuid root).

```
* Es1-2019-02-15: Controllo directory vuota, utilizzo opendir, readdir , inotify nel caso vengano aggiunti file alla directory, stat, fork e wait.
```Text
Questo programma viene attivato con un unico parametro che deve essere una directory vuota
(controllare la coerenza del parametro!).
Quando viene aggiunto un file alla directory questo viene eseguito e cancellato.
```

* Es2-2019-02-15: uguale all Es1 in quanto fork esegue già in modo concorrente.
```C
Si estenda il programma dell'esercizio 1 in modo che se vengono aggiunti molteplici file questi
vengano eseguiti in modo concorrente.
```

* Es3-2019-02-15: Apertura file tramite open, lettura di ogni riga tramite file.readlines, split delle righe tramite str.split e stampa di un programma C su un file C creato.
```Text
Scrivere uno script bash o un programma python che preso in input il file /usr/include/x86_64-linux-
gnu/asm/unistd_64.h crei in output un file .C corretto che contenga la definizione di un array:
 char *syscall_name[] = {
 "read",
 "write",
 ....
 }
 Il vettore syscall_name deve far corrispondere al numero di ogni system call il suo nome come
 stringa.
```

* Es1-2019-01-16: Utilizzo di inotify alla cancellazione di un file e utilizzo di creat. Ricordarsi che se un file è aperto da un processo anche se viene eliminato è ancora leggibile.
```Text
Usando inotify creare il programma neverm che controlli una directory. Ogni volta che viene
 	cancellato un file nella directory sotto osservazione crei un file vuoto di uguale nome. Per esempio
 	eseguendo
 	neverm dir
 	dove dir e' una directory contenente i file a, b, c, anche a seguito dei comandi 'rm dir/a' e 'rm dir/b',
 	dir deve contenere sempre i file a, b e c, a e b saranno file vuoti.
```

* Es2-2019-01-16: utilizzo di readdir e apertura di più file.
```Text
modificare neverm per fare in modo che neverm ripristini anche il contenuto dei file a seguito della
cancellazione (il modo è lasciato alla creatività del candidato)
```

* Es3-2019-01-16: getent passwd, awk per prendere solo alcuni elementi
```Text
getent passwd
 mostra l'intero elenco degli utenti del sistema distribuito del dipartimento in formato passwd(5).
  Scrivere uno script o un programma Python che elaborando opportunamente l'output di 'getent
 passwd' conti gli utenti a seconda della directory dove e' posta la home:
 e.g.
 /home/faculty 65
 /home/students 2496
 ...
 e cosi' via. Il programma deve poter funzionare in sistemi che usano una diversa suddivisione delle
 home degli utenti (cioé nel programma non devono comparire costanti come /home/faculty o simili,
 le categorie devono venir calcolate a partire dal campo 'home' del formato)
```
* Es1-2018-09-21: Utilizzo signalfd, e di conseguenza sigemptyset sigprocmask, sigaddset e kill(utilizzata per mandare segnali). 
```Text
Lo scopo di questo esercizio è di scrivere un programma che usando la system call signalfd quando riceve un
 	segnale SIGUSR1 o SIGUSR2 scriva in un file della directory corrente con nume uguale al pid del processo che ha
 	inviato il segnale, il tipo di segnale ricevuto e l'ora esatta di ricezione del segnale. (se il file non esiste deve essere
 	creato).
 	un esempio di file risultante potrebbe essere:
 	$ cat 20231
 	USR1 Fri Sep 21 10:40:56 CEST 2018
 	USR1 Fri Sep 21 10:40:58 CEST 2018
 	USR2 Fri Sep 21 10:41:26 CEST 2018
```
* Es2-2018-09-21: Utilizzo di fgets per leggere un file, strtok per dividere in pezzi una riga, atoi per convertire stringa in numero e sleep per mettere in pausa il processo.
```Text
Dato un estratto di un file di log come questo:
 Sep 20 19:58:32 eipi ntpd[2051]: Listen normally on 99 eth0 [fe80::8456:a70]:123
 Sep 20 19:58:32 eipi ntpd[2051]: new interface(s) found: waking up resolver
  Sep 20 19:58:34 eipi ntpd[2051]: Soliciting pool server 151.3.106.211
 	Sep 20 19:58:35 eipi ntpd[2051]: Soliciting pool server 94.177.187.22
 	Sep 20 19:58:48 eipi ntpd[2051]: Soliciting pool server 80.211.155.206
 	Sep 20 19:58:49 eipi ntpd[2051]: Soliciting pool server 212.45.144.206
 	Scrivere un programma che lo mostri alla stessa velocita' allla quale e' stato generato.
 In questo caso dovrebbe scrivere le prime dur righe, attendere 2 secondi, mostrare la terza, dopo un secondo la
 quarta quindi dopo una attesa di 13 secondi la quinta e la sesta dopo un ulteriore secondo.
```
Es3-2018-09-21: utilizzo di os walk, controllo se una sottostringa è presente in una stringa.
```Text
Scrivere un programma python o uno script bash che trovi in un sottoalbero tutti i file che hanno come primi
 caratteri '#!' e produca una tabella che elenchi tutti i pathname dei file trovati catalogando insieme i file che
 hanno la stessa prima riga di testo.
 es:
 !/bin/bash: first.sh myscript
 !/usr/bin/env python: prog.py
```

* Es1-2018-07-18: Utilizzo di signalfd, sigemptyset ecc per ricevere i segnali e contare quanti sono.
```Text
Lo scoopo di questo esercizio è di scrivere un programma che conti quanti segnali di tipo SIGUSR1 e quanti di tipo
 	SIGUSR2 riceve. Ogni volta che riceve un segnale di tipo SIGUSR1 deve aumentare un contatore di 1, ogni volta
 	che riceve SIGUSR2 deve decrementare di 1 il contatore. A ogni variazione del contatore il programma stampa il
 valore. Questo programma deve essere realizzato usando la system call signalfd.
```
* Es2-2018-07-18: creazione file in /tmp/, utilizzo signalfd.
```Text
Estendere la soluzione dell'esercizio 1: Modificare il programma dell'esercizio 1 per fare in modo che alla partenza
 	scriva il proprio pid nel file /tmp/countpid. Scrivere poi un secondo programma che lanci il comando con argomenti
 	passato come parametro, prima di eseguire il comando deve mandare SIGUSR1 al programma dell'esercizio 1, al
 	termine deve mandare SIGUSR2.
 	e.g.
 	count sleep 20
 	... spedisce SIGUSR1, esegue sleep 20, manda SIGUSR2. In questo modo il programma dell'esercizio 1 dovrebbe
	contare quanti comandi lanciati con il prgramma count sono in corso di esecuzione.
```
* Es3-2018-07-18: Utilizzo subprocess.run per creare una shell minimale, prendere comandi in input durante l'esecuzione.
```Text
crivere una shell minimale in Python usando la subprocess.run con parametro shell=False.
La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input (^D)

```
* Es1-2018-06-22: utilizzo timerfd per creare uno sleep che aspetta in millisecondi. Ricordarsi che i nanosecondi non sono il numero da aspettare in nanosecondi ma la parte decimale del tempo da aspettare in sec.
```Text
Lo scopo di questo esercizioè di scrivere msleep. msleep si comporta come sleep(1) ma invece di attendere il
 	numero di secondi indicati come parametro deve aspettare il numero di millisecondi indicati come parametro.d
 	es:
 	msleep 2340
 	completa la sua esecuzione in 2340 millisecondi alias 2.34 secondi.
 	La msleep deve essere implementata usando i timerfd (v. timerfd_create(2))
```

* Es2-2018-06-22: Es1 con più timer contemporaneamene, si utilizza poll per aspettare i vari timer e stampare alla fine di ognuno di essi.
```Text
Estendere la soluione dell'esercizio 1: mmsleep (multimsleep) ammette molteplici parametri.
 	msleep 1234 3456 2345
 	allo scadere di 1234 millisecondi stampa 1234, allo scadere di 2345 millisecondi stampa 2345 e infine a 3456
	millisecondi dalla attivazione stampa 3456 ed esce.
 	Questo programma deve essere implementato creando un timerfd per ogni parametro e usando poll(2) per
 	aspettare il prossimo evento.
  
```
* Es3-2018-06-22 Python: shell minimale in python

* Es3-2018-05-29 Bash: Apertura file /proc/*/status, comando ps per vedere i pid dei processi in esecuzione, utilizzo di awk per prendere alcune colonne, e sed per cancellarne alcune. Cat per leggere file e awk per cancellare i duplicati.
```Text
Esercizio 3: Script bash o Python: (10 punti):
I file /proc/*/status contengono importanti informazioni relative ai processi in esecuzione.
 In particolare una riga contiene la costante "Uid:" seguita da quattro numeri (sono l'uid reale, effettivo, salvato e del# file system per il processo in considerazione).
 Scrivere un programma python o uno script bash che per ogni utente che ha un ruolo in almeno un processo
 indichi quanti processi sono attivi che hanno quell'utente come reale, effettivo, salvato o del file system.
 esempio di output:
 0 10 12 12 12
 1000 5 3 3 3
 (l'utente 0 ha 10 processi come utente reale, 12 come effettivo, salvato e del file system. l'utente 1000 ha 5
 processi come utente reale e 3 come effettivo, salvato e del file system. Per esempio questo caso si riferirebbe a
 10 processi di root, 5 dell'utente 1000 dei quali 2 sono setuid root).

```
Es1-2018-02-29: programma per confrontare file in modo parallelo. I processi figli si dividono il file da controllare. Utilizzo di fseek per settare la posizione in cui partire nel file, ftell per trovare la dimensione in byte del file, waitpid per aspettare la terminazion dei processi e le macro WIFEXITED per vedere se il processo ha terminato con exit e WEXITSTATUS per leggere lo status. Kill per terminare il processo.
```Text
Fare un programma di confronto parallelo di file.
 	pcmp file1 file2
 	non stampa nulla se i due file sono uguali altrimenti stampa "file1 file2 differ". pcmp deve creare due processi figli;
 	mentre un processo controlia la prima meta’ del file, l'altro deve controllare l’altra meta’.
 	Se un dei due processi figli trova una differenza, termina immediatamente segnalandolo al padre con opportuno
 	valore di ritorno. In questo caso il padre deve terminare l'altro processo.
 
```
* Es2-2018-02-29: es1 con più processi che si dividono i file. tilizzo di un array di processi e ciclo per farli partire.



* Es3-2018-02-18 Python: utilizzo di .isnumeric e di os.access per vedere il tipo di accesso a un file. 

* Es1-2017-02-17: Utilizzo di utime, stat per accedere ai tempi di modifica e struct utimbuf.
```Text
Scrivere un programma ager in grado di invecchiare file.
 	Il programma deve poter prendere una lista di file come parametri o nessun parametro, nel qual caso invecchierà
 	tutti I file della directory corrente. “invecchiare” significa predatare il tempo di ultimo accesso e di modifica di 10
 	giorni.
 	Esempio:
 	$ ls -l file
 	-rw-r--r-- 1 renzo renzo 0 Feb 17 09:07 file
 	$ ./ager file
 	$ ls -l file
 	-rw-r--r-- 1 renzo renzo 0 Feb 7 09:07 file
```

* Es2-2017-02-17: Es1 con utilizzo di getopt per gestione opzioni.

* Es3-2017-02-17: utilizzo splitext e dictionary

* Es1-2017-0-17: Gestione lista, esplorazione ricorsiva del sottoalbero

* Es2-2017-01-17:  Controllo delle della quantità di hard link associati a ogni file. Gestione lista

* Es3-2017-01-17: Funzione merge, utilizzo dizionari e liste, os.remove per rimuovere file.

### Headers
```C
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <utime.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <pthread.h>
#include <sys/eventfd.h>
#include <sys/inotify.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <inttypes.h>
#include <poll.h>

```
### Syscall 

* int eventfd(unsigned int initval, int flags): crea un eventfd object che può essere utilizzato per aspettare/notificare eventi. L'eventfd object contiene un unsigned int a 64 bit utilizzato come counter. Il counter viene inizializzato con il valore nel primo argomento. Come valore di ritorno, viene ritornato un file descriptor che può essere utilizzato per accedere all'eventfd object. Con la flag EFD_SEMAPHORE eventfd assume la semantica di un semaforo. Infatti se il suo counter ha un valore maggiore di 0, allora la funzione read ritorna il valore 1 e il counter viene decrementato di 1; se invece il counter è zero la chiamata di read provoca il blocco del processo finchè il counter non aumenta. La chiamata alla funzione write aggiunge l'intero da 8 byte(il buffer) al counter(se EFD_SEMAPHRE è attivo sembrerebbe incrementare di 1 il counter).

* int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg) : questa funzione crea un nuovo thread nel processo chiamante. Il nuovo thread iniza l'esecuzione con la l'esecuzione della funzione start_routine(arg). Il thread creato termina se chiama pthread_exit() che specifica l'exit status, il quale è disponibile in un altro thread dello stesso processo che chiama pthread_join(); oppure termina quando ritorna da start_routine() o se viene cancellato con pthread_cancel(). Pthread_join(thread, retval) viene utilizzato per aspettare la terminazione del thread in input, se retval non è NULL in esso viene salvato l'exit status del processo.
```C
// Es produttore e consumatore con evnetfd e pthred_create
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <time.h>

// Puntatore alla variabile condivisa
int *val;

// I due file descriptor utilizzati per i semafori
int eventfdProd;
int eventfdCons;

// Buffer per read e write
uint64_t buf;

void* consumerFunction(void* arg) {
  int readedValue;
  int readedNumbers=10;
  while (readedNumbers > 0) {
    // Se il consumatore può leggere
    if (read(eventfdCons, &buf, sizeof(buf)) > 0) {
      readedValue = *val;
      readedNumbers--;
      printf("Readed number: %d\n", readedValue);
      write(eventfdProd, &buf, sizeof(buf));
      sleep(rand() % 10 + 1);
    }
  }
  return NULL;
}

void* producerFunction(void* arg) {
  int number=0;
  int generatedNumbers=10;

  while (generatedNumbers > 0) {
    // Se il produttore può iniziare a produrre
    if (read(eventfdProd, &buf, sizeof(buf)) > 0) {
      // Produco il numero casuale
      srand(time(NULL));
      do {
        number = rand() % 100 + 1;
      }while(number == *val);

      generatedNumbers--;
      printf("Produced number: %d\n", number);
      *val = number;
      // Rilascio della variabile condivisa
      write(eventfdCons, &buf, sizeof(buf));
      // Attende 
      sleep(rand() % 10);
    }
  }
  return NULL;
}

int main(int argc, char*argv[]) {
  // Allochiamo uno spazio di memoria per la variabile condivisa
  val = (int* )malloc(sizeof(int));
  // Thread per il consumatore e il produttore
  pthread_t consumer;
  pthread_t producer;

  // Inizializziamo i semafori per produttore e consumatore
  // Il consumatore parte con valore 0
  // in quanto non è ancora stato prodotto nulla
  eventfdCons = eventfd(0, EFD_SEMAPHORE);
  
  // Il produttore parte con valore 1 in  
  // quanto è il primo a dover partire
  eventfdProd = eventfd(1, EFD_SEMAPHORE);

  // Creiamo i due thread
  int succesfullStartProd;
  int succesfullStartCons;

  succesfullStartProd = pthread_create(&producer, NULL, producerFunction, NULL);
  if (succesfullStartProd != 0) printf("Error during creation of producer thread\n");

  succesfullStartCons = pthread_create(&consumer, NULL, consumerFunction, NULL);
  if (succesfullStartCons != 0) printf("Error during creation of consumer thread\n");

  pthread_join(producer, NULL);
  pthread_join(consumer, NULL);

  printf("Task completed\n");
  exit(EXIT_SUCCESS);

}
```

* signalfd(int fd, const sigset_t *mask, int flags): crea un file descripotr che può essere usato per accettare segnali che riguardano il chiamante. E' un'alternativa a sigwaitinfo e ha il vantaggio che il file descripotr può essere monitorato utilizzando poll(), select(), e epoll(). L'argomento mask indica i tipi di segnali che devono essere considerati. Se fd è -1 allora viene creato un nuovo file descriptor , se non è -1 deve indicare un file descriptor. Di seguito la struttura standard per utilizzare signalfd. (struct signalfd_siginfo fdsi è dove vengono salvati)
```C
#include <limits.h>
#include <sys/signalfd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define _OPEN_SYS_ITOA_EXT

int main(int argc, char*argv[]) {
sigset_t mask;
int sfd;
struct signalfd_siginfo fdsi;
ssize_t s;
pid_t mainProc = getpid();
// Settiamo la mask su i segnali da ricevere
   sigemptyset(&mask);
   sigaddset(&mask, SIGUSR1);
   sigaddset(&mask, SIGUSR2);

// Controlliamo se siamo nel processo che deve ricevere i segnali
if (fork() != 0){
		// Tramite sigprocmask cambiamo la signal mask
		// standard con quella appena creata
		if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
			handle_error("sigprocmask");
	
		// Creiamo il file descriptor per accetare i segnali
		// indicati dalla mask
		sfd = signalfd(-1, &mask, 0);
		if (sfd == -1)
			handle_error("signalfd");
		// Creiamo il ciclo per ricevere i segnali tramite
		// read()
		for (;;) {
			s = read(sfd, &fdsi, sizeof(fdsi));
			if (s != sizeof(fdsi))
				handle_error("read");

			if (fdsi.ssi_signo == SIGUSR1) {
				char fileName[10];
				time_t currentTime = time(NULL);
				printf("Got SIGUSR1\n");
				// Creiamo il nome del file
				sprintf(fileName, "%d", fdsi.ssi_pid);
				FILE*file = fopen(fileName,"a");
				char* time_str=ctime(&currentTime);
				time_str[strlen(time_str)-1] = '\0';
				fprintf(file, "USR1 %s\n", time_str);
				fclose(file);
			} else if (fdsi.ssi_signo == SIGUSR2) {
				printf("Got SIGUSR2\n");
				char fileName[10];
				time_t currenTime = time(NULL);
				printf("Got SIGUSR2\n");
				// Creiamo il nome del file
				sprintf(fileName, "%d", fdsi.ssi_pid);
				FILE*file = fopen(fileName,"a");
				char* time_str=ctime(&currenTime);
				time_str[strlen(time_str)-1] = '\0';
				fprintf(file, "USR2 %s\n", time_str);
				fclose(file);
			 } else {
			    printf("Read unexpected signal\n");
		    }
		}
```


* kill(int pid, signal): di solito viene utilizzata per terminare processi, ma se si specifica il signal essa permette di mandare al processo identificato dal pid il signal in input. (Utile per testare programmi che ricevono segnali)

* wait(), waitpid().. permettono di bloccare il processo chiamante finchè non ricevono un segnale da un porcesso figlio. Se un processo figlio termina con exit(stat) waitpid prenderà il valore in exit e lo salverà in status(waitpid(pid, &status, 0)) ed è possibile leggere questo valore grazie alla macro WEXITSTATUS.
```C
for (int i=0; i < numberOfProcess; i++) {
		int status;
		if (processes[i]> 0) {
			waitpid(processes[i], &status, 0);
			if (WIFEXITED(status)) {
				if (WEXITSTATUS(status) == 0) {
					printf("%s %s differ\n", file1Path, file2Path);
					for (int k=i; k < numberOfProcess; k++){
						kill(processes[k], SIGTERM);
					}
					fclose(f1);
					fclose(f2);
					return 0;
				}
			}
		}
	}
```
* getopt(argc, argv, "options(se un'opzione prende un valore aggiungere:)"): prende gli argomenti che iniziano con - e il possibile valore successivo viene salvato in optarg. Alla fine l'argomento successivo all'utlima opzione ha indice optind.
```C
int option;
while ((option= getopt(argc, argv, "j:"))!= -1) { 
		switch(option) {
			case 'j':
				numberOfProcess=atoi(optarg);
				break;
			case ':':
				printf("Option require a value\n");
				break;
			default:
				printf("Invalid option\n");
				exit(EXIT_FAILURE);
		}
	}
```

* utime(filePath, struct utimebuf): permette di cambiare il tempo di ultimo accesso e di ultima modifica di un file. Per accedere ai tempi correnti del filre si può utilizzare stat e prendere il campo st_mtime e st_atime. Es:
```C

/*Esercizio 1: Linguaggio C (obbligatorio) 20 punti
 *	Scrivere un programma ager in grado di invecchiare file.
 *	Il programma deve poter prendere una lista di file come parametri o nessun parametro, nel qual caso invecchierà
 *	tutti I file della directory corrente. “invecchiare” significa predatare il tempo di ultimo accesso e di modifica di 10
 *	giorni.
 *	Esempio:
 *	$ ls -l file
 *	-rw-r--r-- 1 renzo renzo 0 Feb 17 09:07 file
 *	$ ./ager file
 *	$ ls -l file
 *	-rw-r--r-- 1 renzo renzo 0 Feb 7 09:07 file
 *
 *
 *
 *
 *
 *
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

int main(int argc, char*argv[]) {
	
	// Se non ha paramteri in input
	// eseguiamo sulla directory corrente
	if (argc == 1) {
		char currentDir[PATH_MAX];
		DIR* dir;
		getcwd(currentDir, sizeof(currentDir));
		dir = opendir(currentDir);
		struct dirent *entry;
		if (dir == NULL){
			printf("Unable to read directory\n");
			exit(EXIT_FAILURE);
}
		while ((entry=readdir(dir)) != NULL) {
			if (entry->d_type & DT_REG) {
				char filePath[PATH_MAX];
				struct utimbuf newTime;
				strcpy(filePath, currentDir);
				strcat(filePath, "/");
				strcat(filePath, entry->d_name);
				// Prendiamo il tempo di modifica corrente del file
				struct stat fileStat;
				stat(filePath, &fileStat);
				// 10 giorni in secondi = 864000
        fileStat.st_atime= fileStat.st_atime - 864000;
        fileStat.st_mtime= fileStat.st_mtime - 864000;
				newTime.actime = fileStat.st_atime;
				newTime.modtime = fileStat.st_mtime;
				utime(filePath, &newTime);
			}
		}
	} else if (argc > 1) {
		for (int i=1; i < argc; i++) {
			struct stat fileStat;
			if (stat(argv[i], &fileStat)==0) {
				struct utimbuf newTime;
			// 10 giorni in secondi = 864000
        fileStat.st_atime= fileStat.st_atime - 864000;
        fileStat.st_mtime= fileStat.st_mtime - 864000;
				newTime.actime = fileStat.st_atime;
				newTime.modtime = fileStat.st_mtime;
				utime(argv[i], &newTime);

			} else {
				printf("Error: stat\n");
				exit(EXIT_FAILURE);
			}
		}
	} 
	return 0;
}
```

* dlopen: serve per lanciare librerie/programmi da un'altro programma, si usa insieme a dlsym che permette di ottenre l'indirizzo della funzione da lanciare. Nel caso di un eseguibile per eseguirlo bisogna utilizzare execvp e fork con ./
```C
/*
Sia dato questo programma hw.c (vi viene fornito in /public/hw.c)
#include <stdio.h>
int main(int argc, char*argv[]) {
printf("hello world:");
for(argv++, argv--; argc > 0; argv++, argc--)
printf(" %s",*argv);
printf("\n");
return 0;
}
Il programma hw.c può essere compilato come libreria dinamica:
gcc --shared -o hw.so hw.c
La libreria dinamica non è un eseguibile
$ ./hw.so 1 2 3 4
Segmentation fault
ma può essere caricata a tempo di esecuzione tramite dlopen. Scrivere un programma "lancia" in
grado di eseguire il codice di hw.so
$ ./lancia hw.so 1 2 3 4
hello world: hw.so 1 2 3 4
(suggerimenti: dlopen non cerca nella directory corrente, occorre passare il path assoluto della libreria.
"main" in hw.so è una normale funzione: occorre cercare l'indirizzo della funzione main nella libreria
ed invocarla,)
 * @version 0.1
 * @date 2022-05-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char*argv[]) {
  void* handle = 0;
  char *error = NULL;
  char dir[PATH_MAX];
  char actualPath[PATH_MAX+1];

  getcwd(dir, sizeof(dir));
  //printf("%s", dir);
  strcat(dir, "/");
  strcat(dir, argv[1]);
  char* realPath = realpath(dir, actualPath);



  handle = dlopen(realPath, RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  // Eliminiamo gli errori esistenti
  dlerror();

  // Chiamiamo dlsym per recuperare l'indirizzo della funzione main
  void (*mainso)(int, char**);
  *(void **)(&mainso) = dlsym(handle, "main");
  error = dlerror();
  if (error != NULL) {
    fprintf(stderr, "%s\n", error);
    exit(EXIT_FAILURE);
  }

  int i=1;
  int elements=0;
  while (argv[i] != NULL) {
    elements++;
    i++;
  }

  // Contiamo gli argomenti in input
  char* arguments[elements]; 
  i=1;
  while (argv[i] != NULL) {
    arguments[i-1] = argv[i];
    i++;
  }

  // Nel caso funzioni dobbiamo dare a main i valori in input
  arguments[i-1]=NULL;
  (*mainso)((int)argc - 1, arguments);
  dlclose(handle);
  exit(EXIT_SUCCESS);

}
```
* dup2(): permette di indirizzare l'output di un eseguibile su un file
```C
// fileno ritorna il file descriptor se si ha una variabile FILE*
int fd1 = fileno(destFile);
          pid_t child;
          int status;
          // esegue il file e scrive il risultato della 
          if ((child = fork()) == 0){
              dup2(fd1, 1);
              close(fd1);
              execvp(command, argumentList);
          }
```

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

* timerfd: permette di creare timer identificati da un file descriptor attraversp timerfd_create. Poi si utilizza timerfd_settime() per settare i valori del timer. In particolare timerfd_settime() prende in input 4 valori, il primo il file descriptor del timer, il secondo una flag(si può settare a 0), il terzo una struttura che setta i valori del timer(it_value.tv_sec è la parte intera del valore da aspettare in secondi, it_value.tv_nsec è la parte decimale in nanosecondi). Il seguente esempio mostra come settare un timer che prende in input valori in milli secondi e setta il timer per aspettare il tempo in input:
```C

/*	Lo scopo di questo esercizioè di scrivere msleep. msleep si comporta come sleep(1) ma invece di attendere il
 *	numero di secondi indicati come parametro deve aspettare il numero di millisecondi indicati come parametro.d
 *	es:
 *	msleep 2340
 *	completa la sua esecuzione in 2340 millisecondi alias 2.34 secondi.
 *	La msleep deve essere implementata usando i timerfd (v. timerfd_create(2))
 *
 *
 */
#include <sys/timerfd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>


int main(int argc, char*argv[]) {
	// Creiamo il timer e salviamo il suo file descriptor
	int timerFd=timerfd_create(CLOCK_REALTIME, 0);
	
	if (timerFd > 0) {
		// Prendiamo il valore in input e lo convertiamo in intero
		int timeInMs= (int)atoi(argv[1]);
		float parteInteraSec= timeInMs/1000;
		float parteDecimaleSec=(timeInMs % 1000)/1000;
		float nanosec=parteDecimaleSec * 1000000000;
		printf("Tempo in sec: %f\n Tempo in nanosec: %f\n", parteInteraSec, nanosec);
		struct itimerspec spec;
		// spec.it_value specifica la scadenza iniziale del timer 
		// in secondi e in nanosecondi. Settare entrambi i valori con un valore 
		// != 0 fa partire il timer.
		spec.it_value.tv_sec = parteInteraSec;
		spec.it_value.tv_nsec = nanosec;
		//spec.it_interval se settato a 0, il timer espirerà solo
		// una volta, mentre seù settato a un valore != 0 specifica il periodo
		// per timer ripetuti.
		spec.it_interval.tv_sec = 0;
		spec.it_interval.tv_nsec = 0;

		timerfd_settime(timerFd, 0, &spec, NULL);
		printf("Timer started\n");


		uint64_t buf;
		ssize_t size;
		size= read(timerFd, &buf, sizeof(uint64_t));
			if (size != sizeof(uint64_t))
				printf("Error: read\n");
		
		
		printf("Timer expired after %d ms\n", timeInMs);
		
	} 
	return 0;
}
```
* poll(): poll permette di avere un insieme di file descriptor e di aspettare gli eventi per ognuno di essi. Può aspettare per un singolo evento oppure per più eventi. Ritorna il numero di eventi che si sono verificati. Di seguito un esempio di utilizzo con timerfd in cui si hanno più timer e si controlla con poll quando scadono.
```C
/*
 * Esercizio 2: Linguaggio C: 10 punti
 *	Estendere la soluione dell'esercizio 1: mmsleep (multimsleep) ammette molteplici parametri.
 *	msleep 1234 3456 2345
 *	allo scadere di 1234 millisecondi stampa 1234, allo scadere di 2345 millisecondi stampa 2345 e infine a 3456
 *	millisecondi dalla attivazione stampa 3456 ed esce.
 *	Questo programma deve essere implementato creando un timerfd per ogni parametro e usando poll(2) per
 *	aspettare il prossimo evento.
 * 
 *
 */

#include <sys/timerfd.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <poll.h>

int main(int argc, char*argv[]) {
	struct pollfd timerPollFd[argc - 1];
	struct itimerspec specs[argc - 1];
	int timesInMs[argc - 1];
	// Creiamo il timer e salviamo il suo file descriptor per
	// ogni valore in input
	for (int i=0; i < argc - 1; i++) {
	timerPollFd[i].fd=timerfd_create(CLOCK_REALTIME, 0);
	timerPollFd[i].events = POLLIN;
	// E' un campo di ritorno e diventa != 0
	// in base al numero di fd che hanno completato
	// il loro task.

	timerPollFd[i].revents = 0;
	timesInMs[i] =(int)atoi(argv[i+1]);
	float parteInteraSec= timesInMs[i]/1000;
	float parteDecimaleSec=(timesInMs[i] % 1000)/1000;
	float nanosec=parteDecimaleSec* 1000000000;
	specs[i].it_value.tv_sec= parteInteraSec;
	specs[i].it_value.tv_nsec = nanosec;

	//spec.it_interval se settato a 0, il timer espirerà solo
	// una volta, mentre se è settato a un valore != 0 specifica il periodo
	// per timer ripetuti.
	specs[i].it_interval.tv_sec = 0;
	specs[i].it_interval.tv_nsec = 0;
	
	timerfd_settime(timerPollFd[i].fd, 0, &specs[i], NULL);
	printf("Timer %d started\n", timesInMs[i]);

	}
	int i=0;
	int timers = argc -1;
	while (timers > 0) {
		int numOfEvents = poll(&timerPollFd[i],1, -1);
		if(numOfEvents > 0) {
			uint64_t buf;
			ssize_t size;
			size= read(timerPollFd[i].fd, &buf, sizeof(uint64_t));
			if (size != sizeof(uint64_t))
				printf("Error: read\n");
			printf("Timer expired after %d ms\n", timesInMs[i]);
			i++;
			timers--;
		}
	}
	for(int i=0; i<argc; i++) {
		close(timerPollFd[i].fd);
	}
	return 0;

}
```
### Snippets:

* Snippet per leggere file con fgets:
```C
char lineToRead[150];
while(fgets(lineToRead, 150, file)!= NULL )
``` 

* Snippet in C per controllare se da la struct stat un file è un eseguibile:
```C
 struct stat file;
        stat(filePath, &file);

        if ((S_IXUSR & file.st_mode)) {
```

* Snippet in C per controllare se una directory è vuota:
```C
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
```

* Snippet di codice per estrarre/spezzare una stringa in base a un carattere inserito attraverso strtok:
```C
token = strtok(lineToRead, " ");
while (token != NULL && i <= 2) {
		token = strtok(NULL, " ");
}
```

* Snippet per aprire un file attraverso fopen:
```C
char filePath[PATH_MAX];
	strcpy(filePath, argv[1]);
	FILE* file= fopen(filePath, "r");

	if (file == NULL) {
		printf("File doesn't found.\n");
        exit(EXIT_FAILURE);
	}
```
* Struttura per testare i segnali utilizzando due processi in parallelo che li mandano:
```C
if(fork() != 0) {
  // codice del processo principale a cui arrivano i segnali
}else {
// Creiamo due processi per testare i signal
	pid_t firstProc;
	pid_t secondProc;
	firstProc = fork();
	if (firstProc == 0) {
		printf("Entered in first process with pid %d\n", getpid());
		kill(mainProc, SIGUSR1);
		sleep(3);
		kill(mainProc, SIGUSR1);
		sleep(4);
		kill(mainProc, SIGUSR2);
		exit(EXIT_SUCCESS);
	}
	secondProc = fork();
	if (secondProc == 0) {
		printf("Entered in second process with pid %d\n", getpid());
		kill(mainProc, SIGUSR2);
		sleep(3);
		kill(mainProc, SIGUSR2);
		sleep(4);
		kill(mainProc, SIGUSR1);
		exit(EXIT_SUCCESS);
	}
}
```
* Snippet per prendere comandi in input:
```C
// Estraiamo il comando in input
char*args[argc];
int i=1;
while (i < argc && argv[i]!= NULL) {
	args[i-1] = argv[i];
	i++;
}
args[i]=NULL;
```

* Funzione per comparare due file settando il punto di partenza e la grandezza del blocco da controllare:
```C
int compareFiles(FILE* file1, FILE* file2, size_t startPoint, size_t blockSize, int processNumber) {
	fseek(file1, startPoint, SEEK_SET);
	fseek(file2, startPoint, SEEK_SET);
	printf("Block size: %ld\n", blockSize);
	char c1=getc(file1);
	char c2=getc(file2);
	size_t i=0;
	while (c1 != EOF && c2 != EOF && i<=blockSize) {
		i++;
		printf("c1: %c id: %d \n", c1, processNumber);
		printf("c2: %c id: %d \n", c2, processNumber);
		if (c1 != c2) {
			return 0;
		}
		c1 = getc(file1);
		c2 = getc(file2);
	}
	return 1;
}

```

* Snippet in C per esplorare un sottoalbero partendo da una directory root
```C
void recursivelyDirectoryExploration(char* rootDir) {
	// Lista per salvare gli inode dei file
	// incontrati
	DIR* dir=opendir(rootDir);
	if (dir == NULL) {
		printf("Error: unable to open directory \"%s\"\n", rootDir);
		exit(EXIT_FAILURE);
	}
	struct dirent* entry;

	while ((entry =readdir(dir))!= NULL) {
		// Esplorando il sottoalbero dobbiamo contare i
		// file
		
		// Se incontriamo una directory
		// dobbiamo entrarci
		if (entry->d_type & DT_DIR) {
			char newDir[PATH_MAX];
			strcpy(newDir, rootDir);
			strcat(newDir, "/");
			strcat(newDir, entry->d_name);
			if(!(strcmp(entry->d_name, "..")==0) && !(strcmp(entry->d_name, ".")==0)) {
				dirCounter++;
				recursivelyDirectoryExploration(newDir);
			}
			// Se è un file regolare
		} else if(entry->d_type & DT_REG) {
			
		}
	}
}

```

* Struttura base per creare liste in C:
```C
typedef struct inodeList {
	ino_t inode;
	struct inodeList* next;
}inodeList;

typedef inodeList* inodeList_ptr;

int isElementInList(inodeList* head, ino_t element) {
	printf("Element inode: %ld \n",element);
	if(head == NULL) {
		return 0;
	}else {
		inodeList* tmp = head;
		while (tmp!=NULL) {
			if (tmp->inode == element) {
				printf("List inode: %ld", tmp->inode);
				return 1;

			}
				
			tmp=tmp->next;
		}
		return 0;
	}
}

void insertElementTail(inodeList_ptr* head, ino_t inode) {
	inodeList_ptr newNode = (inodeList_ptr)malloc(sizeof(inodeList));
	newNode->inode = inode;
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
		return;
	}
	inodeList_ptr tmp = *head;
	while (tmp->next != NULL) {
		tmp=tmp->next;
	}
	tmp->next = newNode;
	return;
}

void insertElementHead(inodeList_ptr* head, inot_t inode) {
	inodeList_ptr newNode = (inodeList_ptr)malloc(sizeof(inodeList));
	newNode->inode = inode;
	newNode->next = NULL;

	if (*head == NULL) {
		*head = newNode;
		return;
	}
	newNode->next = *head;
	*head = newNode;

}

void removeElement(inodeList_ptr* head, ino_t inode) {
	if (*head == NULL) {
		return;
	}

	inodeList_ptr tmp = *head;
	inodeList_ptr prev = NULL;

	if (tmp->inode == inode) {
		*head=tmp->next;
		free(tmp);
		return; 
	}

	while (tmp != NULL) {
		if (tmp->inode == inode) {
			prev->next = tmp->next;
			free(tmp);
			return;
		}
		prev=tmp;
		tmp=tmp->next;
	}

}
```

### Script

#### Python
* Per esplorare i file all'interno di una singola directory utilizzare os.listdir(dir)
```Python
entries = os.listdir(dir)
	for entry in entries:
		name, ext=os.path.splitext(entry)
		if ('.' in ext):
			filesWithSuffix.setdefault(ext, [])
			filesWithSuffix[ext].append(name+ext)
		else:
			filesWithoutSuffix.append(name)
```
* Per ottenere il path assoluto della directory corrente utilizzare os.getcwd(). 

* setdefault permette di creare dizionari con più elementi associati alla stessa chiave:
```Python
filesWithSuffix={}
filesWithSuffix.setdefault(ext, [])
filesWithSuffix[ext].append(name+ext)
```

* per ordinare un dizionario bisogna ordinare con sorted la lista delle chiavi o quella degli elementi:
Es:
```Python
def sortDictionary(dictionary):
    # Estraiamo e ordiniamo dal dizionario i file
		# ordiniamo in ordine alfabetico
    sorted_keys = sorted(dictionary.keys(), key=lambda x: x.lower())

    # Creiamo un dizionario ordinato
    sorted_dict = {}
    for key in sorted_keys:
        sorted_dict[key] = dictionary[key]

    return sorted_dict

```

* Per esplorare un sottoalbero di directory si utilizza os.walk. Esso per ogni direcotory restituisce i file all'interno, il path della directory e i nomi delle directory all'interno.
Es:
```Python
for dirPath, dirNames, files in os.walk(sys.argv[1]):
      # Inseriamo ogni file presente nella directory corrente nel dizionario
      # e associamo a ogni file la directory a cui appartiene
        for file in files:
            lastModTime = os.path.getmtime(os.path.join(dirPath, file))
            subTree.setdefault(lastModTime, [])
            subTree[lastModTime].append(file)
    sort = sorted(subTree.keys())
    print(sort)
    print(
        f'\nLast modified file: {subTree[sort[-1]]}, date of modification: {sort[-1]}')
    print(
        f'\nFile modified earlier: {subTree[sort[0]]}, date of modification: {sort[0]}')
```

* Per ottenere l'utlimo tempo di modifica di un file in python si utilzza os.path.getmtime().
Es:
```Python
lastModTime = os.path.getmtime(os.path.join(dirPath, file))
```

* Per ottenere l'ultimo tempo di accesso a un file o la data di creazione si utilizza os.stat().

* Per dividere il nome di un file in nome e estensione si utilizza os.splitext(nome file)
Es
```Python
fileName, fileExt = os.path.splitext(file)
```
* I for per andare da un valore all'altro utilizzano range(start, end, step)
```Python
for i in range(1, len(sys.argv), 1):
```
* os.scandir() restituisce un os.DirEntry che permette ad accedere a informazioni sui file all'interno di una directory. In particolare è possibile ottenere l'inode e altre informazioni.
Es
```Python
 dirEntries = os.scandir(dirPath)
    for entry in dirEntries:
      pathname.setdefault(entry.inode(), [])
      pathname[entry.inode()].append(os.path.join(dirPath, entry.name))
  
```
* Per controllare gli elementi all'interno di una directory os.path. offre alcuni metodi come os.path.isfile per capire se un path è un file o no.
Es
```Python
 if os.path.isfile(os.path.join(dir, file)):
```
* filecmp.cmp serve per confrontare due file, di default l'opzione shallow è True, quindi confronta la size, la data di modifica ecc ma non il contenuto effettivo. Per confrontare il contenuto bisogna mettere shallow = False.
Es:
```Python
if filecmp.cmp(f, os.path.join(dir, file), shallow=False) == True:
```
* Per eliminare un file si utilizza os.remove(path).

* Per creare un hard link si utilizza os.link(filePointedPath, nameOfLinkFile).

* Per creare un symbolic link si utilizza os.symlink(filePointedPath, nameOfSymlinkFile).

* Funzione per contare le linee di un file.
```Python
def countLines(fileName):
  file = open(fileName, "r")
  counter = 0
  text = file.read()
  textList = text.split('\n')

  for lines in textList:
    if lines:
      counter+=1
  return counter
```
* In python per convertire un tipo in un altro basta fare str(int) o int (str).

* Per leggere le linee di un file si utilizza file.readline(), dopo aver aperto un file tramite open(path, mod).
```Python
openedFile = open(os.path.join(dirPath, file), "r")
firstLine = openedFile.readline()
```

* Per leggere comandi scritti da linea di comando durante l'esecuzione si può utilizzare sys.stdin.readline()

* Per splittare una stringa in base al carattere basta avere una stringa e fare .split("carattere su cui splittare")
```Python
text.split("\n")
```
* Un file aperto può anche essere letto tramite file.read(byte da leggere) che restituisce come stringa i byte letti. Se non si mette nulla in input il valore è -1 ovvero legge l'intero file.

* Per eseguire comandi del terminale si può usare subprocess.run(command, shell=False), che restituisce un oggetto CompletedProcess al completamento. Su questo oggetto è possibile controllare il valore ritornato dal comando eseguito tramite returnValue.check_returncode().
```Python
import subprocess
returnValue = subprocess.run(commands, shell=False)
returnValue.check_returncode()
```

* Per controllare se si ha accesso a un file in scrittura, lettura ecc si utilizza os.access(path, mod)

* Per controllare se una stringa rappresenta un numero si può utilizzare stringa.isnumeric()

* Per scrivere stringhe con più linee la si racchiude tra ''' '''.
```Python
stringa= '''
  #include<stdlib.h>
  #include<stdio.h>

  int main() {
    char *syscall_name[446];
  '''
```

* Per copiare file da una cartella all'altra la libreria shutil fornisce il metodo .copy(pathfile, destpath). 
```Python
import shutil
	for f in filesToCpy:
		shutil.copy(f, destDir)
		os.remove(f)
```
#### Bash

* Es4(inviare la mail da terminale):
```Bash
mail -s "PROVAPRATICA" -A es1_cognome.c -A es2_cognome.c -A es3_cognome.bash renzo@cs.unibo.it
```


* Es0: Rendete la vostra directory home inaccessibile ad altri utenti (sia in lettura che in esecuzione). Si puo’
tenere una sola directory in /public che abbia come nome il vostro username e.g.
“/public/giovanni.rossi” e che abbia permessi 700
```Bash
chmod o-rx /home/students/your.name

# in /public
mkdir your.name
chmod 700 /public/your.name
```

* Per vedere i pid dei processi attivi utilizzare:
```Bash
ps -e > process.txt
```
* Per correggere l'indentazione di un file .c si può utilizzare il comando:
```Bash
ex -n '+norm!gg=G' +wq
```

* Per prendere in input il primo elemento da terminale si usa la variabile $# che indica il numero di argomenti:
```Bash
if [[ $# -gt 0 ]]
then 
  path=${1}
fi

```
* $0 indica il nome dello shell script

* find analizza ricorsivamente i path contenuti in pathlist e applica expression ad ogni file (find pathlist expression).
Expression ha una determinata sintassi:	
	* -name pattern: find è true se il nome del file fa match con pattern
	* -perm permission: True se permission corrisponde ai permessi del file
	* -print stampa il pathname del file e ritorna true
	* -ls stampa gli attributi del file e ritorna true
	* - user username, -uid userId True se il possessore del file è username/password
	* -group groupname, -gid groupId True se il gruppo del file è groupname/groupId
	* -atime | -mtime | -ctime -count True se il file è stato acceduto | modificato | oppure cambiati gli attributi negli ultimi count giorni
	* -type b|c|d|p|f|l|s True se il file è di tipo a blocchi | a caratteri | directory | nmaned pipe | file regolare | link |socket
	* -not, !, -a, -and, -o, -or operatori logici
```Bash
find $path -name "*.c" -exec ex -n '+norm!gg=G' +wq {} \;
```
* Per dichiarare le varaibili basta il nome, per accedere al valore bisogna usare $

* Utilizzare eval per usare come comandi una variabile
```Bash
eval $output
```
* & lancia processi in parallelo

* getent passwd mostra l'elenco degli utenti

* Per modificare un file in loco cancellando solo determinate stringhe si può usare sed
```Bash
# Esempio in cui si lasciano solo le righe che contengono /home
sed -i '\|:/home/|!d' passwd.txt
```
* awk: la parte dentro begin viene eseguita solo una volta all'inizio, la parte in END viene eseguita solo alla fine, la parte fuori viene eseguita su ogni riga. Per leggere le righe di un file con awk bisogna specificare il nome del file dopo ''.
```Bash
# Esempio con awk per dividere ogni riga del file in pezzi spezzando a ogni :
awk '
  {
    str=$0
  
    split(str, arr, ":")

    print arr[6]
  }
  
  ' passwd.txt > users.txt
```
* Per eliminare duplicati da un file usare:
```Bash
awk '!seen[$0]++' realuid.txt 
```
* Con > si indirizza l'output su un file sovrascrivendo il contenuto, con >> si fa append

* In awk $1, $2 ecc fanno riferimento alle colonne in cui si può dividere una riga.

* Per scorrere gli elementi in un'array usare:
```Bash
# dichiaro array vuoto
declare -a uids=()

while read line; do
  uids+=($line)
done < realuid.txt

# leggo gli elementi
for uid in "${uids[@]}"; do
  realCounter=0
  effectiveCounter=0
  savedCounter=0
  fsysCounter=0
```
* Per eliminare tutte le linee vuote da un file usare:
```Bash
sed -i '/^$/d' list.txt
```
* Per creare il testo di un file bisogna scriverlo in una stringa e fare printf "$cProgram" > file.c.
```Bash
cProgram+='
  int i;
  
  if(argc > 1) {
    if (isNumber(argv[1])) {
      int index = atoi(argv[1]);
      if (index >=424) index-=90;
      printf("%%s \\n", syscall[index]);
      return 0;
    }
    else {
      for (int i = 0; i < 357; i++) {
        int index = i;
        if (i >= 335) index = i + 90;
        if(strcmp(argv[1], syscall[i])==0) {
          printf("%%d \\n", index);
          return 0;
        }
      }
    }
    printf("Error, syscall not found");
    return 1;
  }
}
'
printf "$cProgram" > file.c
``` 

* Per prendere il contenuto di un file si può utilizzare cat
```Bash
# Salviamo un file con gli Uid per ogni processo
while read line; do
  cat /proc/${line}/status > status${line}.txt
  awk '$1 ~ "Uid:"' status${line}.txt > uid${line}.txt
  rm status${line}.txt
done < pid.txt
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
* Linux non ha itoa quindi si deve usare sprintf:
```C
sprintf(string, "%d", number_to_convert);
```
* Per far partire la lettura di un file da un punto diverso da quello iniziale si può utilizzare fseek(file, offset in byte che viene aggiunto alla partenza, punto di partenza). Insieme ad fseek se si usa ftell si può calcolare la dimensione di un file in byte.
```C
fseek(f1, 0L, SEEK_END);
size_t sizeFile1= ftell(f1);

```
* La funzione basename(path) può essere utilizzata per estrarre il nome del file da un path.

* La funzione ftell si può usare per sapere la dimensione in byte dei file se si mette il cursore del file alla fine.
```C
fseek(f1, 0L, SEEK_END);
size_t sizeFile1= ftell(f1);

```

## Web Tecnologies