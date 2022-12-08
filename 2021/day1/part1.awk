#!/usr/bin/awk -f
BEGIN { count = 0; size = 0; }
{
    if (count > 0)
        current = $0;
        if (current > previous)
            size++;
    count++;
    previous = $0;
}
END { print size; }
