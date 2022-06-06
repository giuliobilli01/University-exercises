#!/usr/bin/python
#
#
#Esercizio 3: Script bash o Python: (10 punti):
#	Scrivere uno script che faccia il merge dei contenuti due directory:
#	merge a b c
#	Tutti i file (non le directory) esistenti in a e in b devono essere spostati in c. Nel caso due file con lo stesso nome
#	compaiano sia in a sia in b, il file spostato in c deve essere quello piu' recentementente modificato, l’altro deve
#	rimanere nella directory di origine.
#
#
import os
import sys
import shutil

def main():
	dir1=''
	dir2=''
	destDir=''
	if (len(sys.argv)) >= 4:
		dir1=sys.argv[1]
		dir2=sys.argv[2]
		destDir=sys.argv[3]
	else:
		print("Error, invalid number of arguments\n")
	
	# Salviamo in un dizionario i path dei file
	# utilizzando come chiave il nome
	# in questo modo gli elementi che hanno lo stesso nome
	# sono associati alla stessa chiave e semplificano il confronto. 
	filesToMerge={}
	entries1 = os.listdir(dir1)
	# Inseriamo gli elementi della prima cartella
	for entry in entries1:
		filesToMerge[entry]= (os.path.join(dir1, entry))
	
	entries2 = os.listdir(dir2)
	for entry in entries2:
		lastModTime2 = os.path.getmtime(os.path.join(dir2, entry))
		if (entry in filesToMerge): 
			lastModTime1 = os.path.getmtime(filesToMerge[entry])
			if (lastModTime2 > lastModTime1):
				filesToMerge[entry]=os.path.join(dir2, entry)
		else:
			filesToMerge[entry] = (os.path.join(dir2, entry))
	
	# Arrivati qui filesToMerge dovrebbe contenere i path con i file
	# più aggiornati di entrambe le directory
	# quindi li copiamo nella directory in cui eseguire il merge
	filesToCpy = []
	keys = filesToMerge.keys()
	for key in keys:
		#print(filesToMerge[key])
		filesToCpy.append(filesToMerge[key])
	
	print(f'files: {filesToCpy}\n')
	for f in filesToCpy:
		shutil.copy(f, destDir)
		os.remove(f)

if __name__=='__main__':
	main()


