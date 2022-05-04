
/**
 * @file EsC-1.c
 * @author Giulio Billi
 * @brief passaggio di dati uno o centomila ma non nessuno.
 * Scrivere un monitor con due procedure entry:
 * put(T dato);
 * T get(void);
 * Esistono due tipi di processo: gli scrittori che chiamano put e i lettori che chiamano la get.
 * La put deve fare in modo che tutti i lettori in attesa, qualora ve ne siano, ricevano il dato passato come parametro. Se
 * non ci sono lettori in attesa la put deve attendere la prima chiamata della procedure entry get e trasferire il dato. Se ci
 * sono già scrittori in attesa, il nuovo scrittore si mette in coda (ordine FIFO).
 * La get quindi se c'è uno scrittore in attesa deve ritornare il dato del primo scrittore in attesa (e sbloccare lo scrittore),
 * altrimenti deve attendere la prossima chiamata della procedure entry put.
 * Domanda ulteriore: è possibile implementare il monitor con una sola variabile di condizione? Perché?
 * --> No perchè abbiamo due tipi di processi che eseguono le operazioni del monitor in determinati casi. Con un unica coda
 *     ad esempio, quando viene eseguita la signal nella funzione entry get si andrebbero a sbloccare non solo i processi writer in attesa ma anche i reader.
 * @version 0.1
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

monitor rw
{

  // Contatori per i processi in waiting
  int waitingToRead;
  int waitingToWrite;

  // Dato tenuto dal monitor
  T datoMonitor;

  // Varaibili di condizione per read e write
  condition cWrite, cRead;

  // Funzione di inizializzazione
  rw()
  {
    waitingToRead = 0;
    waitingToWrite = 0;
  }
  // Procedure entry (pubbliche)
  entry T get()
  {
    if (waitingToWrite > 0)
    {
      cWrite.signal();
      return datoMonitor;
    }
    else
    {
      waitingToWrite++;
      cwrite.wait();
      // Se dopo la wait riprende subito
      // waitingToWrite--;
    }
  }

  entry put(T dato)
  {
    if (waitingToRead > 0)
    {
      datoMonitor = dato;
      while (waitingToRead > 0)
        cRead.signal();
      waitingToRead--;
    }
    else if (waitingWrite > 0)
    {
      waitingToWrite++;
      cWrite.wait();
      // Nel caso in cui dopo la wait riprenda da qui
      // datoMonitor = dato;
      // waitingToWrite--;
    }
  }
}

// In es c.1 2012 24 maggio la condizione di deadlock si verifica se il santuario è pieno e il ponte è pieno di gente che va verso il santuario
// quindi bisogna aggiungere una condizione

// Il wprking set serve per stimare la quantità di pagine dche un processo richiede in modo da evitare situazioni di trashing in cui i processi si rubano le pagine a vicenda