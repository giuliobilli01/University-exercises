#!/bin/bash
# Esercizio 3: Python o bash: (10 punti):

# Rielaborando l'output del comando:

# echo "#include<sys/syscall.h>" | gcc -dD -E -

# scrivere un programma python o uno script bash che generi automaticamente un programma C che

# consenta di associare ogni syscall al suo numero e viceversa.

# es: "sysnumber fork" deve restituire 57 mentre "sysnumber 72" deve avere come risposta fnctl

# (l'esempio si riferisce a sistemi di architettura x86_64)


echo "#include<sys/syscall.h>" | gcc -dD -E - > list.txt
# Rimuove tutte  le linee vuote dal file
sed -i '/^$/d' list.txt
# Lascia solo le linee in cui sono presenti i numeri e i nomi delle syscall
sed -i '/^#define __NR_/!d' list.txt

awk '
  {str = $2
  
  split(str, arr, "NR_")

  print arr[2]
  }
  
  ' list.txt > syscall.txt

declare -a syscalls=()

index=0
while read line; do
  syscalls+=($line)
done < syscall.txt


cProgram='
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isNumber(char* arg) {
  while(*arg != 0 || *arg != "\\n") {
    if (*arg < '0' || *arg > '9')
      return 0;
    arg++;
  }
  return 1;
}

int main(int argc, char* argv[]) {
  char *syscall[] = {'

  for value in "${syscalls[@]}"
do
  cProgram+='"'${value}'"'
  cProgram+=','
done

cProgram+='};'

cProgram+='
  int i;
  
  if(argc > 1) {
    if (isNumber(argv[1])) {
      int index = atoi(argv[1]);
      if (index >=424) index-=90;
      printf("%%s \\n", syscall[index]);
      return 0;
    }
    else {
      for (int i = 0; i < 357; i++) {
        int index = i;
        if (i >= 335) index = i + 90;
        if(strcmp(argv[1], syscall[i])==0) {
          printf("%%d \\n", index);
          return 0;
        }
      }
    }
    printf("Error, syscall not found");
    return 1;
  }
}
'

rm list.txt syscall.txt
printf "$cProgram" > file.c