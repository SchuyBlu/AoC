#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
    int flag = 0;
    int index = 0, hori = 0, vert = 0, value, num;
    char input, string[15], dist;
    input = getchar(); 
    while (input != EOF) {
        if (input == '\n') {
            value = dist - '0';
            if (strcmp(string, "up") == 0)
                vert -= value;
            else if (strcmp(string, "down") == 0)
                vert += value;
            else
                hori += value;
            flag = 0;
            index = 0;
            input = getchar();
            continue;
        }
        if (input == ' ') {
            string[index] = '\0';
            flag = 1;
            index = 0;
        }
        if (flag) {
            dist = input;
        }
        else {
            string[index] = input;
            index++;
        }
        input = getchar();
    }
    printf("%d\n", vert * hori);
    return 0;
}

