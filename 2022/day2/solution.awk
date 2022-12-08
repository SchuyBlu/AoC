#!/usr/bin/gawk -f
BEGIN { 
    (res["AZ"] = "3026") && (res["AX"] = "1330") && (res["AY"] = "2613");
    (res["BZ"] = "3636") && (res["BX"] = "1010") && (res["BY"] = "2323");
    (res["CZ"] = "3316") && (res["CX"] = "1620") && (res["CY"] = "2033");
}
{
    part1 += substr(res[$1$2], 1, 1) + substr(res[$1$2], 2, 1);
    part2 += substr(res[$1$2], 3, 1) + substr(res[$1$2], 4, 1);
}
END { printf "Part 1: %d\nPart 2: %d\n", part1, part2; }
