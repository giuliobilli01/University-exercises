# File System

## Semantica della coerenza
Non sempre le modifiche ad un file aperto sono visibili agli altri processi immediatamente. Nel caso dell sessioni AFS, se un file viene modificato da un processo, tutti quelli che lo hanno già aperto non vedono la modifica mentre chi lo apre vede la nuova versione.

## Tecniche per garantire coerenza 
L'utilizzo del caching introduce il problema dell'incosistenza nel file system ad esempio a causa di interruzioni di corrente.
QUeste sono alcune soluzioni

### Curare
* fsck è un comando dei sistemi operativi Unix e Unix-like che effettua il controllo della coerenza dei dati presenti in un file system e, in caso di perdita parziale o totale di essi, ne permette, se possibile, il recupero dati. Inoltre, è in grado di richiamare badblocks, il che gli consente anche di individuare i cluster danneggiati, e di contrassegnarli in modo da impedire al sistema di accedervi in futuro. Solitamente fsck è eseguito automaticamente all'avvio del sistema per rilevare velocemente eventuali inconsistenze, ed in tal caso è eseguito nuovamente per effettuare controlli più approfonditi e tentare di porre rimedio agli errori rilevati; l'amministratore di sistema può tuttavia invocarlo manualmente sulla riga di comando in caso di problemi con i file system in uso. Normalmente fsck può operare solo su file system non montati, o quantomeno montati in sola lettura. In caso contrario, la modifica concorrente del file system da parte del sistema operativo e di fsck può portare ad una perdita di dati. 

* ScanDisk esegue la scansione del disco rigido per individuare errori, mentre l'utilità di deframmentazione dischi riorganizza tutte le informazioni presenti sul disco per ottimizzare le prestazioni del sistema.

### Prevenire

* ext3: è un file system utilizzato su sistemi GNU/Linux e derivato da ext2, rispetto al quale migliora la scrittura su disco rendendo più facile e più veloce leggere i vari file dal disco, inoltre introduce il journaling del file system. Il journaling, già presente in ReiserFS e nelle ultime versioni di NTFS è una caratteristica che permette di evitare che errori e malfunzionamenti hardware (o anche semplici spegnimenti del PC senza chiudere il sistema operativo) possano danneggiare i dati scritti sull'unità, creando un "diario" (journal) che elenca le modifiche da effettuare sul filesystem. Quando un applicativo invia dei dati al file system per memorizzarli su disco, questo prima memorizza le operazioni che intende fare su un file di log e in seguito provvede a effettuare le scritture sul disco rigido, quindi registra sul file di log le operazioni che sono state effettuate. In caso di caduta di tensione durante la scrittura del disco rigido, al riavvio del sistema operativo il file system non dovrà far altro che analizzare il file di log per determinare quali sono le operazioni che non sono state terminate e quindi sarà in grado di correggere gli errori presenti nella struttura del file system. Poiché nel file di log vengono memorizzate solo le informazioni che riguardano la struttura del disco (metadati), un'eventuale caduta di tensione elimina i dati che si stavano salvando, ma non rende incoerente il file system. 

* ReiserFS: ReiserFS è un file system progettato e implementato da un team di programmatori guidati da Hans Reiser. È correntemente supportato solo dal kernel Linux, ma potrà essere incluso in altri sistemi operativi nel futuro. Con la versione 2.4.1 di Linux, ReiserFS è stato il primo journaling file system ad essere incluso nel kernel vanilla. 

## File system distribuitit

* NFS: Il NFS permette ai calcolatori che compongono un sistema distribuito di condividere file, directory o un intero file system utilizzando il protocollo client-server. Un calcolatore (client) deve richiedere esplicitamente ad un altro calcolatore (server) del sistema distribuito di condividere una directory o un file, dichiarando un punto di montaggio. Una volta effettuato un montaggio un utente sul calcolatore client accede alla directory montata in modo assolutamente trasparente, ossia accede alla directory remota credendo di accedere ad una directory locale. 

* SMB: SMB agisce con un approccio client-server, per cui un client avanza le sue richieste ed il server risponde opportunamente. Una sezione del protocollo è dedicata specificatamente all'accesso al file system, in modo che i client possano fare richieste al file server, ma ci sono altre sezioni specializzate per le comunicazioni tra processi. SMB è stato ottimizzato per l'uso in rete locale, ma può essere usato anche attraverso Internet.

I server SMB rendono il loro file system e le altre risorse disponibili ai client sulla rete. I client possono avere i loro propri dischi che non sono pubblicamente accessibili ed accedere comunque al file system condiviso e alle stampanti del server, e questa è la modalità primaria di utilizzo del protocollo. 