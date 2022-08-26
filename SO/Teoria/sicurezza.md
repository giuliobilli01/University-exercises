# Sicurezza

## Protezione e controllo d'accesso
TCB o Trusted Computing Base è l'insime di hardware e firmware e/o software che sono critici per la sicurezza, quindi un bug o una vulnerabilità compromette la sicurezza del sistema. Essi dipendono dalle politiche di sicurezza del sistema.

## Posix 
Il gruppo POSIX ha cercato di standardizzare adiverse problematiche relative alla sicurezza:

* Mandatory access control: è un metodo per limitare l'accesso alle risorse basato sulla sensibilità delle informazione contenute dalle risorse e sui permessi degli user per accedere a informazioni con un determinato livello di sensibilità.
Si definisce la sensibilità di una risorsa con un security label. Il security label è composto da un livello di sicurezza e zero più categorie di sicurezza(The security category defines the category or group to which the information belongs (such as Project A or Project B)).

* Audit: con il termine audit si intendono delle procedure di controllo che servono a valutare se dei processi soddisfano certi criteri e direttive.