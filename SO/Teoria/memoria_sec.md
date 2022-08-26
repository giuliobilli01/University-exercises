# Memoria secondaria

## NAS
Una Network Attached Storage (NAS) è un dispositivo collegato alla rete la cui funzione è quella di consentire agli utenti di accedere e condividere una memoria di massa, in pratica costituita da uno o più dischi rigidi, all'interno della propria rete o dall'esterno. Generalmente i NAS sono dei computer attrezzati per poter comunicare via rete. Pertanto, non sono dei semplici dispositivi di memorizzazione di dati da connettere via RJ-45 a dei computer, ma sono, a tutti gli effetti, degli storage il cui scopo è mettere a disposizione spazio disco in rete in maniera "intelligente" ovvero interfacciabile, gestibile e collegabile ad altre risorse di rete, in primis i server su cui sono installati le applicazioni e il Domain controller. 

## SAN
In informatica e telecomunicazioni una Storage Area Network (SAN) è una rete o parte di una rete ad alta velocità di trasmissione (generalmente Gigabit/sec) costituita esclusivamente da dispositivi di memorizzazione di massa, in alcuni casi anche di tipi e tecnologie differenti. Il suo scopo è quello di rendere tali risorse di immagazzinamento (storage) disponibili per qualsiasi computer (generalmente application server e DBMS server) connesso ad essa.[1] I protocolli attualmente più diffusi, usati per la comunicazione all'interno di una SAN, sono FCP (Fibre Channel Protocol) ed iSCSI (Internet SCSI). 

## RAID
La velocità dei processori cresce secondo la legge di Moore mentre la velicità dei sispositivi di memoria è molto più lenta quindi è necessario aumentarne le prestazioni in altri modi.
Oltre a metodi per eseguire le richieste sul disco in modo efficente si può utilizzare il parallelismo attraverso array di dischi indipendenti in grado di gestire più richieste in parallelo.(i dati letti in parallelo devono essere su dischi indipendenti per evitare conflitti)
Lo schema RAID è uno standard industriale per l'utilizzo di più dischi in parallelo e ha 7 schemi diversi con alcune caratteristiche in comune: array di dischi visti dal SO come un unico disco singolo, i dati sono distribuiti tra i vari dischi, la capacità ridondante dei dischi può essere utilizzata per memorizzare informazioni di parità o altri metodi per il recupero delle informazioni in casi di guasti.

### RAID 0
Non è un vero e proprio membro della famiglia RAID in quanto non contiene meccanismi di ridondanza per gli errori, infatti viene utilizzato per applicazioni in cui l'affidabilità non è un grosso problema. I dati vengono distribuiti su dischi differenti quindi se due richieste riguardano blocchi di dati differenti è probabile siano su due dischi differenti e quindi possono essere servite in parallelo. I dati nell'unico disco logico vengono suddivisi in STRIP (settori, blocchi o altri multipli), e strip consecutivi sono distribuiti su dischi diversi in modo da aumentare le performance della lettura di dati sequenziali.
RAID 0 è efficente per grandi trasferimenti di dati con quantità di dati più grande degli strip e anche per un gran numero di richieste indipendenti in cui la quantità di dati è paragonabile a quella degli strip.

### RAID 1
Ottiene la ridondanza duplicando tutti i dati su due insiemi indipendenti di dischi, quindi ha una copia di ogni disco. Anche questo è basato su striping ma qui ogni strip viene scritto su due dischi diversi.(il costo per unità di memorizzazione raddoppia).
Di conseguenza ogni operazioni di lettura può essere risolta da entrambi i dischi che contengono l'informazione richiesta mentre l'operazione di scrittura richiede che vengano modificati tutti i dischi che contengono il dato.
La ridondanza creata dai dischi copia permette il recovery delle informazioni danneggiate in uno dei dischi.

### RAID 3
Più dischi forniscono un unico volume dato dalla loro somma meno uno (quattro dischi da 10 TB, ad esempio, fornivano un volume da 30 TB), dato che l’ultimo disco era destinato alla parità, nel senso che interveniva per garantire il corretto funzionamento anche nel caso uno dei dischi risultasse danneggiato (sino al suo ripristino).

### RAID 4
Utilizza stripe relativamente grandi e ha un disco utilizzato per la parità. Infatti viene calcolato uno strip di parità a partire dagli strip di dati corrispondenti, calcolato bit per bit che viene poi inserito nel disco di parità. In una lettura senza guasti si individua lo strip contenente i dati e si effettua la lettura, in una lettura con guasti si leggono gli altri strip per poi confrontarli con il disco di parità e ottenere lo strip mancante.
In caso di scrittura senza guasti si hanno performance peggiori perchè va letto e aggiornato il bit di parità. Per farlo però non è necessario leggere tutti gli strip ma solo tre in quanto:
Per calcolare il nuovo strip di parità si dovrebbe fare: S'4(i) = S0(i) xor S'1(i) xor S2(i) xor S3(i)
Noi sappiamo che fare xor tra due valori identici è un identità A xor A = A
Quindi se facciamo: S'4(i) = S0(i) xor S'1(i) xor S1(i) xor S1(i) xor S2(i) xor S3(i)
Abbiamo  S0(i) xor S1(i) xor S2(i) xor S3(i) = S 4(i) ovvero lo strip di parità precedente
Quindi possiamo ridurci a fare: S'4(i) = S4(i) xor S'1(i) xor S1(i)

### RAID 5
come RAID 4, ma i blocchi di parità sono sparsi fra i vari dischi, il vantaggio è che non esiste un disco di parità che diventa un
bottleneck. In particolare lo strip di parià è assegnato ciclicamente, ovvero negli strip da 0 a 3 è nel disco 5, per quelli da 4 a 7 è nel disco 4, per quelli da 8 a 11 è nel disco 3 ecc. In questo modo abbiamo un aumento delle prestazioni anche in scrittura.

### RAID 6
utilizza due strip di parità invece di uno, in modo da tollerare due dischi di guasto ma non il terzo, a differenza di 4 e 5 che tollerano solo un disco guasto.
Quindi nel RAID-6, il blocco di parità viene generato e distribuito tra due stripe di parità, su due dischi separati, usando differenti stripe di parità nelle due direzioni.
Il RAID-6 è più ridondante del RAID-5, ma è molto inefficiente quando viene usato in un numero limitato di dischi.

