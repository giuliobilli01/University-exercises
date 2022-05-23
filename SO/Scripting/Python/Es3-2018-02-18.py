################################
#
# Esercizio 3: Script bash o Python: (10 punti):
# Le directory di tipo /proc/nnn/fd (dove nnn e' un numero) mostrano i descrittori di file aperti dai processi.
# Scrivere uno script bash o un programma python che mostri quali processi stanno usando piu' descrittori,
# (ad alcune directory /proc/nnn e' vietato l'accesso perche' sono di altri utenti, saltatele nella scansione)
# 
################################

import os
import glob

def main():
  dir = '/proc/'
  for element in os.listdir(dir):
    if element.isnumeric():
      if os.access(dir + element + "/fd/", os.R_OK):
        fd=os.listdir(dir + element + "/fd/")
        if len(fd) > 1:
          print(f'Process {element} is using more of one file descriptor: {fd}\n')



if __name__ == '__main__':
  main()






