#!/bin/bash
# Esercizio 3: Python o bash: (10 punti)
# Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi
# para.py sleep 20 // ls -l // ps // sleep 3
# para.sh sleep 20 // ls -l // ps // sleep 3
# deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti

if [[ $# -gt 0 ]]; then
  output=""
  for input in $*
  do
    if [[ $input = "//" ]]; then 
      output+=" &"
    else
      output+=" "
      output+=$input
    fi
  done
  eval $output
fi