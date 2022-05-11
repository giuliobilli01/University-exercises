# Esercizio 3: Python o bash: (10 punti)
# Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi
# para.py sleep 20 // ls -l // ps // sleep 3
# para.sh sleep 20 // ls -l // ps // sleep 3
# deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti

import os
import sys
import subprocess

def main():

  string = ''

  for i in range(1, len(sys.argv), 1):
    if sys.argv[i] != '//':
        string += ' ' + sys.argv[i]
    else:
      string += ' &'

  print(string)
  
  os.system(f'{string}')

if __name__ == '__main__':
  main()