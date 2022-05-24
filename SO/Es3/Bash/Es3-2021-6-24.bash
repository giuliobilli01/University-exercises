#!/bin/bash

# Esercizio 3: Python o bash: (10 punti)
# Scrivere uno script o un programma python che corregga l'indentazione di tutti i file .c e .h presenti
# nel sottoalbero della directory passata come parametro (la working directory se non vi sono
# parametri).
# Hint: il comando:
# ex -n '+norm!gg=G' +wq prog.c
# corregge l'indentazione del programma sorgente C prog.c.

path=`echo -n pwd`
if [[ $# -gt 0 ]]
then 
  path=${1}
fi
echo $path
find $path -name "*.c" -exec ex -n '+norm!gg=G' +wq {} \;
