#!/usr/bin/awk -f
BEGIN { hori = 0; vert = 0; }
{
    if ($1 == "up")
        vert -= $2
    else if ($1 == "down")
        vert += $2
    else
        hori += $2
}
END { print (hori * vert); }

