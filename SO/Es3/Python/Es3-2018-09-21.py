################################
# Esercizio 3: Python o bash: (10 punti):
#
# Scrivere un programma python o uno script bash che trovi in un sottoalbero tutti i file che hanno come primi
# caratteri '#!' e produca una tabella che elenchi tutti i pathname dei file trovati catalogando insieme i file che
# hanno la stessa prima riga di testo.
# es:
# !/bin/bash: first.sh myscript
# !/usr/bin/env python: prog.py
#
################################

import os
import sys

def isScript(file):
  firstLine = file.readline()
  if "#!" in firstLine:
    file.close()
    return True
  else:
    file.close()
    return False


def main():
  dir=''
  if len(sys.argv) > 1:
    dir = sys.argv[1]
  else:
    dir = os.getcwd()

  subTree = {}
  for dirPath, dirNames, files in os.walk(dir):
    for file in files:
      if os.path.isfile(os.path.join(dirPath, file)):
        openedFile = open(os.path.join(dirPath, file), "r")
        if isScript(openedFile):
          openedfile = open(os.path.join(dirPath, file), "r")
          line = openedfile.readline()
          tempFirstLine = line.split("#")
          firstLine= tempFirstLine[1].split("\n")
          subTree.setdefault(firstLine[0], [])
          subTree[firstLine[0]].append(os.path.join(dirPath, file))

          
  print(subTree)
if __name__ == '__main__':
  main()






