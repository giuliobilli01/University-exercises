################################
#
# Esercizio 3: Python o bash: (10 punti):
# Scrivere uno script bash o un programma python che preso in input il file /usr/include/x86_64-linux-
# gnu/asm/unistd_64.h crei in output un file .C corretto che contenga la definizione di un array:
# char *syscall_name[] = {
# "read",
# "write",
# ....
# }
# Il vettore syscall_name deve far corrispondere al numero di ogni system call il suo nome come
# stringa.
#
################################
from re import search, match

def main():

  file = open("/usr/include/x86_64-linux-gnu/asm/unistd_64.h", "r")
  syscall_names = []

  textList = file.readlines()
  print ("\n")
  for line in textList:
   splittedLine = line.split(" ")
   if (len(splittedLine)>=2):
    words = splittedLine[1].split("NR_")
    if len(words) >= 2:
     syscall_names.append(words[1])
  
  file.close()
  
  stringa= '''
  #include<stdlib.h>
  #include<stdio.h>

  int main() {
    char *syscall_name[446];
  '''
  index = 0
  for name in syscall_names:
    if index == 335:
      index+=90
    stringa+=f'syscall_name[{index}]="{name}";\n'
    index+=1
  stringa+='''
  }
  '''
  fileC = open("output.c", "w")
  fileC.write(stringa)
  fileC.close()


if __name__ == '__main__':
  main()







