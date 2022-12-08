#!/usr/bin/ruby
input = File.read("input").split

total1 = 0
total2 = 0
for a in input
  b = a.split(/,|-/).map! {|x| x = Integer(x)}
  if (b[0] <= b[2] and b[1] >= b[3]) or (b[0] >= b[2] and b[1] <= b[3])
    total1 += 1
  end
  if (b[0]..b[1]).include? b[2] or (b[0]..b[1]).include? b[3] or (b[2]..b[3]).include? b[0] or (b[2]..b[3]).include? b[1]
    total2 += 1
  end
end

print "Part 1: ", total1, "\n"
print "Part 2: ", total2, "\n"
