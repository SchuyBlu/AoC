#!/usr/bin/awk -f
BEGIN { hori = 0; vert = 0; aim = 0; }
{
    if ($1 == "up")
        aim -= $2;
    else if ($1 == "down")
        aim += $2;
    else {
        hori += $2;
        vert += aim * $2;
    }
}
END { print (hori * vert); }

