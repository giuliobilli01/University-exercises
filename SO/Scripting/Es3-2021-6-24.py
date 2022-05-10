# Esercizio 3: Python o bash: (10 punti)
# Scrivere uno script o un programma python che corregga l'indentazione di tutti i file .c e .h presenti
# nel sottoalbero della directory passata come parametro (la working directory se non vi sono
# parametri).
# Hint: il comando:
# ex -n '+norm!gg=G' +wq prog.c
# corregge l'indentazione del programma sorgente C prog.c.
import os
import sys


def main():
    # Definiamo un dictionary vuoto in cui verrà salvato il sottoalbero
    subTree = []
    # Controllo presenza directory come parametro
    if len(sys.argv) > 1:
		arg = sys.argv[1]
	else:
		arg = os.curdir
    # Eseguiamo un for per percorrere l'intero sottoalbero in input
    for dirPath, dirNames, files in os.walk(arg):
      # Inseriamo ogni file presente nella directory corrente nel dizionario
      # e associamo a ogni file la directory a cui appartiene
        for file in files:
            fileName, fileExt = os.path.splitext(file)
            if (fileExt == '.c' or fileExt == '.h'):
                subTree.append(os.path.join(dirPath, file))

    for path in subTree:
      os.system(f"ex -n '+norm!gg=G' +wq {path}")
      
if __name__ == "__main__":
    main()
