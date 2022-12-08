#!/usr/bin/gawk -f
BEGIN { count = 1; prev = 0; psum = 0; }
{
    arr[count - 1] = $1;
    if (length(arr) == 3) {
        if (prev != 0 && (arr[0] + arr[1] + arr[2]) > prev)
            psum++;
        prev = arr[0] + arr[1] + arr[2];
    }
    if (count == 3) 
        count = 0; 
    count++;
}
END { print psum; }

