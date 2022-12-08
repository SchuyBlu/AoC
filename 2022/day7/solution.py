#!/usr/bin/python3

dirs = []
sizes = []
with open("input", "r") as data:
    for l in data:
        line = l.strip().split()
        if line[0] == "$":
            if line[1] == "cd":
                if line[2] == "..":
                    sizes.append(dirs.pop())
                    if dirs != []:
                        dirs[-1] += sizes[-1]
                else:
                    dirs.append(0)
        if line[0].isdigit():
            dirs[-1] += int(line[0])
while dirs != []:
    sizes.append(dirs.pop())
    if dirs != []:
        dirs[-1] += sizes[-1]
print(sum(value for value in sizes if value <= 100000))

sizes.sort()
unused = 70000000 - sizes[-1]
need = 30000000 - unused
i = 0
while sizes[i] <= need:
    i += 1
print(sizes[i])
