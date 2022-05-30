################################
#
# Esercizio 3: Python o bash: (10 punti):
# Scrivere un programma python o uno script bash che cerchi tutti i file con uguale contenuto in una
# directory. I file con lo stesso contenuto devono diventare link fisici a un unico file.
#
################################

import os
import sys
import filecmp


def main():

  directory = {}

  dir = ''
  if len(sys.argv) > 1:
    dir = sys.argv[1]
  else:
    dir = os.getcwd()

  # Raggruppiamo i file uguali nel dizionario
  files = os.listdir(dir)
  for file in files:
    if os.path.isfile(os.path.join(dir, file)):

      if len(directory.keys()) == 0:
        directory.setdefault(os.path.join(dir, file), [])
      else:
        isEqual = False
        for f in directory.keys():
          if filecmp.cmp(f, os.path.join(dir, file), shallow=False) == True:
            directory[f].append(os.path.join(dir, file))
            isEqual = True
        if not isEqual:
          directory.setdefault(os.path.join(dir, file), [])
  
  # Trasformiamo i file con lo stesso contenuto in hard link
  for file in directory.keys():
    for element in directory[file]:
      os.remove(element)
      name, ext = os.path.splitext(element)
      name+= "(link)"
      name+=ext
      os.link(file, name)

if __name__ == "__main__":
  main()


