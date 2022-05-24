################################
#
# Esercizio 3: Python o bash: (10 punti):
# Scrivere un programma python o uno script bash che calcoli il numero di righe presenti in tutti i file .c,
# .h, e Makefile (o makefile).
# Prima deve stampare ogni per ogni file .c il numero di righe, poi il totale righe per tutti i file .c,
# similmente per i file .h e i makefile e alla fine il totale generale;
# e.g.
# primo.c 100
# secondo.c 150
# dir/terzo.c 120
# tot .c 370
# primo.h 10
# dir/terzo.h 24
# tot .h 34
# Makefile 44
# dir/makefile 22
# tot Makefile 66
# tot source 470 
#
################################

import os
import sys

def stampa(ls, tot, ext):
  for file in ls:
    print(f'{file}\n')
  print(f'tot {ext} {tot}\n')


def countLines(fileName):
  file = open(fileName, "r")
  counter = 0
  text = file.read()
  textList = text.split('\n')

  for lines in textList:
    if lines:
      counter+=1
  return counter

def main():
  
  # Per comodità si può inserire la directory su cui eseguire lo script
  dir = ''
  if len(sys.argv) > 1:
    dir = sys.argv[1]
  else:
    dir = os.getcwd()

  filesDict = {}
  cFilesList = []
  hFilesList = []
  makeFilesList = []


  totLinesCounter = 0
  totC = 0
  totH = 0
  totMake = 0

  for dirPath, dirName, files in os.walk(dir):
    for file in files:
      fileName, fileExt = os.path.splitext(file)
      if(fileExt == '.c'):
        lines = countLines(os.path.join(dirPath, file))
        totC+= lines
        totLinesCounter+=lines
        cFilesList.append(os.path.join(dirPath, file) + " " + str(lines))
      elif(fileExt == '.h'):
        lines = countLines(os.path.join(dirPath, file))
        totH+= lines
        totLinesCounter+=lines
        hFilesList.append(os.path.join(dirPath, file) + " " + str(lines))
      elif(fileName == 'Makefile'):
        lines = countLines(os.path.join(dirPath, file))
        totMake+= lines
        totLinesCounter+= lines
        makeFilesList.append(os.path.join(dirPath, file) + " " + str(lines))
  
  # Fase di stampa
  stampa(cFilesList, totC, '.c')
  stampa(hFilesList, totH, '.h')
  stampa(makeFilesList, totMake, 'make')
  print(f'tot source {totLinesCounter}')


if __name__ == '__main__':
  main()