#Esercizio 3: Python: (10 punti):
#Scrivere una shell minimale in Python usando la subprocess.run con parametro shell=False.
#La shell deve eseguire comandi con o senza parametri e terminare con logout o fine del file di input (^D)




import subprocess
import sys
import os


def main():
  commands = []
  while True:
    input = sys.stdin.readline()
    if "." in input:    
      if os.path.isfile(input):
        file = open(input, "r")
        text = file.read()
        commands= text.split("\n")
    else:
      line = input.split("\n")
      commands = line[0].split(" ")
      print(line)
    if commands:
      returnValue = subprocess.run(commands, shell=False)
      returnValue.check_returncode()
      
      print ("Task completed successfully")
    else:
      sys.exit(0)

if __name__ == "__main__":
  main()
