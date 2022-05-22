#!/bin/bash
# Esercizio 3: Script bash o Python: (10 punti):
# I file /proc/*/status contengono importanti informazioni relative ai processi in esecuzione.
# In particolare una riga contiene la costante "Uid:" seguita da quattro numeri (sono l'uid reale, effettivo, salvato e del
# file system per il processo in considerazione).
# Scrivere un programma python o uno script bash che per ogni utente che ha un ruolo in almeno un processo
# indichi quanti processi sono attivi che hanno quell'utente come reale, effettivo, salvato o del file system.
# esempio di output:
# 0 10 12 12 12
# 1000 5 3 3 3
# (l'utente 0 ha 10 processi come utente reale, 12 come effettivo, salvato e del file system. l'utente 1000 ha 5
# processi come utente reale e 3 come effettivo, salvato e del file system. Per esempio questo caso si riferirebbe a
# 10 processi di root, 5 dell'utente 1000 dei quali 2 sono setuid root).


ps -e > process.txt

# Creiamo un file contenente tutti i pid dei processi 
awk '{print $1}' process.txt > pid.txt

sed -i '\|PID|d' pid.txt

# Salviamo un file con gli Uid per ogni processo
while read line; do
  cat /proc/${line}/status > status${line}.txt
  awk '$1 ~ "Uid:"' status${line}.txt > uid${line}.txt
  rm status${line}.txt
done < pid.txt


while read pid; do
  awk '{ print $2}' uid${pid}.txt >> realuid.txt
  awk '{ print $3}' uid${pid}.txt >> effectiveuid.txt
  awk '{ print $4}' uid${pid}.txt >> saveduid.txt
  awk '{ print $5}' uid${pid}.txt >> fsysuid.txt

  rm uid${pid}.txt
done < pid.txt

awk '!seen[$0]++' realuid.txt > realuidUniq.txt
awk '!seen[$0]++' effectiveuid.txt > effectiveuidUniq.txt
awk '!seen[$0]++' saveduid.txt > saveduidUniq.txt
awk '!seen[$0]++' fsysuid.txt > fsysuidUniq.txt

declare -a uids=()

while read line; do
  uids+=($line)
done < realuid.txt

for uid in "${uids[@]}"; do
  realCounter=0
  effectiveCounter=0
  savedCounter=0
  fsysCounter=0

  # Contiamo i processi con realUid = uid
  while read id; do
    if [[ uid = id ]]; then
      realCounter+=1
    fi
  done < realuid.txt

  # Contiamo i processi con effectiveUid = uid
  while read id; do
    if [[ uid = id ]]; then
      effectiveCounter+=1
    fi
  done < effectiveuid.txt

  # Contiamo i processi con savedUid = uid
  while read id; do
    if [[ uid = id ]]; then
      savedCounter+=1
    fi
  done < saveduid.txt

  # Contiamo i processi con fsysUid = uid
  while read id; do
    if [[ uid = id ]]; then
      fsysCounter+=1
    fi
  done < fsysuid.txt

  printf "%d %d %d %d\n" "$uid" "$realCounter" "$effectiveCounter" "$fsysCounter" >> result.txt
done

rm realuid.txt realuidUniq.txt effectiveuid.txt effectiveuidUniq.txt saveduid.txt saveduidUniq.txt fsysuid.txt fsysuidUniq.txt pid.txt process.txt



