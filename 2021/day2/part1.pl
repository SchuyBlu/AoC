#!/usr/bin/perl
use feature "say";
open (my $fh, "<", "input") or die "Can't open file";
my $vert = 0;
my $hori = 0;
while (<$fh>) {
    chomp $_;
    my @temp = split(" ", $_);
    if ($temp[0] eq "up") { 
        $vert -= $temp[1];
    }
    elsif ($temp[0] eq "down") {
        $vert += $temp[1];
    }
    else {
        $hori += $temp[1];
    }
}
say $hori * $vert;
