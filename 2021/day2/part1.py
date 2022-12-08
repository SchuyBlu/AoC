#!/usr/bin/python3
vert = 0
hori = 0
with open("input", "r") as filehandle:
    for line in filehandle.readlines():
        line = line.strip()
        opt, dist = line.split(" ")
        if (opt == "up"):
            vert -= int(dist)
        elif (opt == "down"):
            vert += int(dist)
        else:
            hori += int(dist)
print(vert * hori)
