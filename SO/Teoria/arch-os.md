# Architettura dei sistemi operativi

## Progettazione di un sistema operativo
La progettazione prende in considerazione:

* La definizione del problema: consiste nel definire gli obbiettivi del sistema che si vuole realizzare e i costraint in cui si opera

* La progettazione dipende dall'hardware e dalle applicazioni: al livello più basso la progettazione è influenzata dall'hardware e al livello pù alto dalle applicazione che deve eseguire il SO.

* Queste condizione portano alla creazione di un sistema che può essere di diversi tipi:
  * batch: un sistema batch è un SO in cui non si ha interazione tra processi, oppure si ha un esecuzione accorpata di più programmi, oppure l'esecuzione non è immediata ma rimandata nel tempo oppure in cui si ha la modifica di più dati contemporaneamente.
  
  * time-shared: sistemi operativi in cui l'uso delle risorse di processamento viene suddivisa in quanti di tempo e ogni quanto è asseganto a un processo (di uno o più utenti)

  * real-time: un sistema real-time deve garantire che una elaborazione (o task) termini entro un dato vincolo temporale o scadenza (detta in gergo deadline). Per garantire questo è richiesto che la schedulazione delle operazioni sia fattibile. Il concetto di fattibilità di schedulazione è alla base della teoria dei sistemi real-time ed è quello che ci permette di dire se un insieme di task sia eseguibile o meno in funzione dei vincoli temporali dati.

  * single-user: il SO può essere utilizzato da un solo utente per volta.

  * multi-user: il SO può essere utilizzato da più utenti contemporaneamente attraverso l'utilizzo di un terminale per ogni utente.

  * general-purpose: spesso utilizzati nei server e hanno la caratteristica di essere usati per l'esecuzione di task eterogenee.
