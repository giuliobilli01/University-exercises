################################
# Esercizio 3: Python o bash: (10 punti):
# Scrivere un programma python o uno script bash che faccia l'elenco dei pathname in un sottoalbero
# che sono link fisici fra loro:
# e.g.
# searchln mydir
# mydir/a mydir/d/b mydir/qq
# mydir/uno mydir/due
# significa che i path mydir/a mydir/d/b mydir/qq fanno riferimento allo stesso file, cosi' come mydir/uno
# mydir/due indicano uno stesso file (diverso dal precedente).
# Nel sottoalbero possono esserci molteplici altri file, se hanno un solo nome non vengono indicati
# nell'output.
#
################################

import os
import sys

def main():
  pathname = {}

  dir = ''
  if len(sys.argv) > 1:
    dir = sys.argv[1]
  else:
    dir = os.getcwd()
  
  for dirPath, dirName, files in os.walk(dir):
    dirEntries = os.scandir(dirPath)
    for entry in dirEntries:
      pathname.setdefault(entry.inode(), [])
      pathname[entry.inode()].append(os.path.join(dirPath, entry.name))
  
  for inode in pathname.keys():
    print(f'{pathname[inode]}\n')
  

if __name__ == "__main__":
  main()