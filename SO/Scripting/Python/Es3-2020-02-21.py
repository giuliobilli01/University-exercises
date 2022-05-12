# Esercizio 3: Python o bash: (10 punti)
# Scrivere un programma python o uno script bash che produca il listato del contenuto di una directory
# in ordine di suffisso.
#
#
#

import os
import sys

def main():
  files = {}
  dir = ''
  if len(sys.argv) > 1:
    dir = sys.argv[1]
  else:
    dir = os.getcwd()
  
  for file in os.listdir(dir):
    fileName, fileExt = os.path.splitext(file)
    files.setdefault(fileExt, [])
    files[fileExt].append(fileName)

  sortedExt = sorted(files.keys())

  print("I file della directory in ordine di estensione sono:")
  for ext in sortedExt:
    print(f'{files[ext]}{ext}\n')    



if __name__ == "__main__":
  main()





