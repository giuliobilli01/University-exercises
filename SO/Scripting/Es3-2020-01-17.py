# Esercizio 3: Python o bash: (10 punti)
# Scrivere un programma python o uno script bash che consenta di lanciare parallelamente comandi
# para.py sleep 20 // ls -l // ps // sleep 3
# para.sh sleep 20 // ls -l // ps // sleep 3
# deve eseguire concorrentemente i vari comandi separati da // e aspettare la terminazione di tutti

import os
import sys
import subprocess

def main():
  commands = []
  string = []

  for i in range(1, len(sys.argv), 1):
    if sys.argv[i] != '//':
        string.append(sys.argv[i])
    else:
      commands.append(string[0:])
      string.clear()
  commands.append(string[0:])
  
  

  processes = []

  for command in commands:
    process = subprocess.Popen(command, shell=True)
    processes.append(process)  

  for p in processes:
    output = p.wait()
  
  print(output)

if __name__ == '__main__':
  main()