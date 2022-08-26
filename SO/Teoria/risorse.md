# Risorse

Un sistema di elaborazione è composto da un insieme di risorse da assegnare ai processi presenti i quali competono per l'accesso ad esse.

Le risorse si possono dividere in classi. Le risorse appartenenti alla stessa classe sono equivalenti e ogni risorsa viene detta istanza della classe. Il numero di risorde in una classe viene detto molteplicità del tipo di risorsa.
Un processo non può chiedere una specifica risorsa ma solo una specifica classe.

## Assegnazione delle risorse

* Le risorse sono ad assegnazione statica quando l'assegnamento avviene al momento della creazione del processo e rimane valida fino alla terminazione.

* Le risorse ad assegnazione dinamica invece vengono richieste dai processi durante l'esecuzione e le utilizzano una volta ottenute per poi rilasciarle quando non sono più necessarie(periferiche I/O).

## Tipi di richieste
Le richieste possono essere:

* Singole: in cui viene richiesta una singola risorsa di una singola classe

* Multiple: in cui vengono richieste più risorse di più classi

* Richiesta bloccante: Se il processo non riceve la risorsa richiesta si blocca finchè non la riceve 

* Richiesta non bloccante: Se il processo non riceve la risorsa non si bloccca 

## Tipi di risorse
* Risorse non condivisibili: risorse che non possono essere assegnate contemporaneamente a più processi.

* Risorse condivisibili: risorse che possono essere assegnate a più processi contemporaneamente.

* Risorse prerilasciabili: una risorsa è prerilasciabile se può essere sottratta a un processo prima che esso l'abbia rilasciata. Quando una risorsa viene prerilasciata il processo si blocca e successivamente la risorsa verrà riassegnata al processo.

* Risorse non prerilasciabili: risorse che non possono essere sottratte al processo prima del rilascio.



