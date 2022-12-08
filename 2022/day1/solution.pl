#!/usr/bin/perl
use strict;
use warnings;
use feature "say";

my $curr_cals = 0;
my @arr = ();
open my $fh, "<", "input" or die "Cannot open file";
while (<$fh>) {
    chomp $_;
    if ($_ eq "") {
        push @arr, $curr_cals;
        $curr_cals = 0;
    }
    else {
        $curr_cals += $_;
    }
}
push @arr, $curr_cals;
@arr = sort { $b <=> $a } @arr;
say "Part 1: ", $arr[0];
say "Part 2: ", $arr[0] + $arr[1] + $arr[2];
close $fh;

