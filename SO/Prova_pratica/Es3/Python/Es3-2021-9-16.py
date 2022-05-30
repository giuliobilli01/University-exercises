# Esercizio 3: Python o bash: (10 punti)
# Scrivere un programma/script che faccia la lista riscorsiva dei file in un sottoalbero riportando in
# ordine alfabetico per nome di file in quale/quali sottodirectory compare.
# e.g.
# rlsr mydir
# ciao: . ./a
# mare: ./a ./b
# sole: .
import os
import sys


def sortDictionary(dictionary):
    # Estraiamo e ordiniamo dal dizionario i file
    sorted_keys = sorted(dictionary.keys(), key=lambda x: x.lower())

    # Creiamo un dizionario ordinato
    sorted_dict = {}
    for key in sorted_keys:
        sorted_dict[key] = dictionary[key]

    return sorted_dict


def main():
    # Definiamo un dictionary vuoto in cui verrà salvato il sottoalbero
    subTree = {}
    # Eseguiamo un for per percorrere l'intero sottoalbero in input
    for dirPath, dirNames, files in os.walk(sys.argv[1]):
      # Inseriamo ogni file presente nella directory corrente nel dizionario
      # e associamo a ogni file la directory a cui appartiene
        for file in files:
            subTree.setdefault(file, [])
            subTree[file].append(dirPath)

    # Ordiniamo i file in ordine alfabetico
    subTree = sortDictionary(subTree)
    # Stampiamo il sottoalbero con i file ordinati
    files = subTree.keys()
    for file in files:
        print(f'{file}: {subTree[file]}\n')


if __name__ == "__main__":
    main()
