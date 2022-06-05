#!/usr/bin/python
#
#Esercizio 3: Script bash o Python: (10 punti):
#Il programma deve elencare I file della directory corrente divisi per suffisso (e al termine l’elenco di quelli privi di
#suffisso.
#es:
#.c: primo.c var.c main.c
#.h: primo.h const.h
#.odt: relazione.odt
#makefile README COPYING
#
#
#

import os



def main():
	dir = os.getcwd();
	filesWithSuffix={}
	filesWithoutSuffix = []
	
	entries = os.listdir(dir)
	for entry in entries:
		name, ext=os.path.splitext(entry)
		if ('.' in ext):
			filesWithSuffix.setdefault(ext, [])
			filesWithSuffix[ext].append(name+ext)
		else:
			filesWithoutSuffix.append(name);
	
	extensions=filesWithSuffix.keys()
	for ext in extensions:
		print(f'{ext}: {filesWithSuffix[ext]}\n')
	for element in filesWithoutSuffix:
		print(f'{element} ')


if __name__=='__main__':
	main()







