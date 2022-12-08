#!/usr/bin/python3
all_elves = []
current = 0
with open("input", "r") as filehandle:
    for line in filehandle:
        if line == "\n":
            all_elves.append(current)
            current = 0
        else:
            current += int(line)
all_elves.append(current)
all_elves.sort(reverse=True)
print(f"Part 1: {all_elves[0]}")
print(f"Part 2: {all_elves[0] + all_elves[1] + all_elves[2]}")
