#!/usr/bin/python3
from string import ascii_letters
totals = [0, 0]
file = open("input", "r")
fl = [elem for elem in file]
for n, line in enumerate(fl):
    char = ''.join(set(line[:len(line)//2]) & set(line[len(line)//2:]))
    totals[0] += ascii_letters.find(char) + 1
    if n % 3 == 0:
        badge = ''.join(set(fl[n]) & set(fl[n + 1]) & set(fl[n + 2])).strip()
        totals[1] += ascii_letters.find(badge) + 1
print(f"Part 1: {totals[0]}\nPart 2: {totals[1]}")
file.close()

