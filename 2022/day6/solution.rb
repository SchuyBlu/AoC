#!/usr/bin/ruby
input = File.read("input").chars
p1c = nil
p2c = nil
for i in 0..input.length-4
    if (!p1c) && input.slice(i, 4).uniq.length == 4
      p1c = i + 4
    end
    if (!p2c) && input.slice(i, 14).uniq.length == 14
      p2c = i + 14
    end
end
print "Part 1: ", p1c, "\nPart 2: ", p2c, "\n"

