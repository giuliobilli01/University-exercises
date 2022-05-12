# Esercizio 3: Python o bash: (10 punti)
# Scrivere uno script in grado si cercare all'interno di un sottoalbero del file system il file modificato più
# di recente e quello la cui ultima modifica è avvenuta più anticamente.
#
import os
import sys
import time


def main():
    tot_files = []
    # Definiamo un dictionary vuoto in cui verrà salvato il sottoalbero
    subTree = {}
    # Eseguiamo un for per percorrere l'intero sottoalbero in input
    for dirPath, dirNames, files in os.walk(sys.argv[1]):
      # Inseriamo ogni file presente nella directory corrente nel dizionario
      # e associamo a ogni file la directory a cui appartiene
        for file in files:
            lastModTime = os.path.getmtime(os.path.join(dirPath, file))
            subTree.setdefault(lastModTime, [])
            subTree[lastModTime].append(file)
    sort = sorted(subTree.keys())
    print(sort)
    print(
        f'\nLast modified file: {subTree[sort[-1]]}, date of modification: {sort[-1]}')
    print(
        f'\nFile modified earlier: {subTree[sort[0]]}, date of modification: {sort[0]}')


if __name__ == "__main__":
    main()
