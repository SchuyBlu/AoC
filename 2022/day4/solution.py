#!/usr/bin/python3
import re
total1, total2 = 0, 0
with open("input", "r") as file:
    for i in file:
       i = list(map(int, re.findall(r'\d+', i)))
       total1 += (i[0] <= i[2] and i[1] >= i[3]) or (i[0] >= i[2] and i[1] <= i[3])
       total2 += bool(set(range(i[0], i[1] + 1)) & set(range(i[2], i[3] + 1)))
print(f"Part 1: {total1}\nPart 2: {total2}")

