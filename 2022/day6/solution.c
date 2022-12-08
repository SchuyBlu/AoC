#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool quickcheck(char b[4], int len)
{
    int temp;
    int added = 0;
    for (int i = 0; i < len; i++) {
        temp = b[i] - 'a';
        if (added & (1 << temp))
            return false;
        added = added | (1 << temp);
    }
    return true;
}

int main(int argc, char** argv)
{
    char d[14], b[4];
    uint32_t count = 0, p1c = 0, p2c = 0;
    char c;
    while ((c = getchar()) != EOF) {
        for (int i = 0; i < 13; i++) {
            if (i < 3) b[i] = b[i + 1];
            d[i] = d[i + 1];
        }
        b[3] = c; d[13] = c;
        if (!p1c && count >= 3 && quickcheck(b, 4))
            p1c = count + 1;
        if (!p2c && count >= 13 && quickcheck(d, 14))
            p2c = count + 1;
        count++;
    }
    printf("Part 1: %d\nPart 2: %d\n", p1c, p2c);
    return 0;
}

