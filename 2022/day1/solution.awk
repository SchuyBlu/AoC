#!/usr/bin/gawk -f
BEGIN { curr_cals = 0; count = 0;}
{
    if ($1 == "") {
        arr[count] = curr_cals;
        curr_cals = 0;
        count += 1;
    }
    curr_cals += $1; 
}
END { 
    arr[count] = curr_cals; 
    n = asort(arr); 
    print "part 1:", arr[n];
    print "part 2:", arr[n] + arr[n - 1] + arr[n - 2]; 
}
