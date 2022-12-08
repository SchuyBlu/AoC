#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
int main(int argc, char **argv)
{
    int flag = TRUE;
    int vert = 0, hori = 0;
    char string[15], dist;
    char* line = NULL;
    size_t len = 0, size = 0;
    size = getline(&line, &len, stdin);
    while (size != -1) {
        for (int i = 0; i < size; i++) {
            if (line[i] != '\n') {
                if (line[i] == ' ') {
                    string[i] = '\0';
                    flag = FALSE;
                }
                if (flag)
                    string[i] = line[i];
                else
                    dist = line[i];
            }
        }
        flag = TRUE;

        // Write rules
        if (strcmp(string, "up") == 0)
            vert -= dist - '0';
        else if (strcmp(string, "down") == 0)
            vert += dist - '0';
        else
            hori += dist - '0';
        size = getline(&line, &len, stdin);
    }
    printf("%d\n", vert * hori);
    free(line);
    return 0;
}
