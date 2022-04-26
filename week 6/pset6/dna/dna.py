import csv
import sys


def biggene(dna, gene):
    maxcount = 0
    counter = 0
    continuous = False
    lim = len(gene) - len(dna) + 1
    i = 0
    while i < lim:
        sample = gene[i: i + len(dna): 1]
        if sample == dna and continuous == True:
            counter += 1
            i = i + len(dna)
        if sample == dna and continuous == False:
            counter = 1
            i = i + len(dna)
            continuous = True
        if sample != dna and continuous == True:
            continuous = False
            maxcount = max(maxcount, counter)
            i = i + 1
        if sample != dna and continuous == False:
            i = i + 1
    maxcount = max(maxcount, counter)
    return maxcount


if len(sys.argv) != 3:
    print("Usage: python dna.py database.csv sequence.txt")
    sys.exit(1)

suspects = []

with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        suspects.append(row)

dnas = []

for key in suspects[0].keys():
    if key != 'name':
        dnas.append(key)

noofstrs = []

for dna in dnas:
    f = open(sys.argv[2], "r")
    gene = f.read()
    f.close()
    val = biggene(dna, gene)
    noofstrs.append(str(val))

found = False

for sus in suspects:
    if found == False:
        counter = 0
        for i in range(len(dnas)):
            if sus[dnas[i]] == noofstrs[i]:
                counter += 1
        if counter == len(dnas):
            found = True
            print(sus['name'])

if found == False:
    print("No match")