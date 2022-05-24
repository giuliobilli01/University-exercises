#!/bin/bash
#
# Esercizio 3: Python o bash: (10 punti):
# getent passwd
# mostra l'intero elenco degli utenti del sistema distribuito del dipartimento in formato passwd(5).
# Scrivere uno script o un programma Python che elaborando opportunamente l'output di 'getent
# passwd' conti gli utenti a seconda della directory dove e' posta la home:
# e.g.
# /home/faculty 65
# /home/students 2496
# ...
# e cosi' via. Il programma deve poter funzionare in sistemi che usano una diversa suddivisione delle
# home degli utenti (cioé nel programma non devono comparire costanti come /home/faculty o simili,
# le categorie devono venir calcolate a partire dal campo 'home' del formato)
################################

getent passwd > passwd.txt

sed -i '\|:/home/|!d' passwd.txt

awk '
  {
    str=$0
  
    split(str, arr, ":")

    print arr[6]
  }
  
  ' passwd.txt > users.txt

# Eliminiamo duplicati delle home da cercare e lo Inseriamo in un file a parte
sort users.txt | uniq -u > homes.txt

declare -a userHome=()

while read line; do
  userHome+=($line)
done < homes.txt

# Confrontiamo tutte le home con quelle salvate e contiamo quanti user hanno la stessa home
for home in "${userHome[@]}"
do
  stringa=''
  counter=0
  while read line; do
    if [[ home = line ]]; then
      counter = $counter + 1
    fi
  done < users.txt
  stringa+=$home
  stringa+='\t'
  stringa+=$counter
  stringa+='\n'
  printf $stringa
done

rm homes.txt passwd.txt users.txt


  
