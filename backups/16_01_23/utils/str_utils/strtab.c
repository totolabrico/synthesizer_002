#include "main.h"

int strintab(char **strs, char *str)
{
	int i;

    i = 0;
    while(strs[i])
    {
        if (strcmp(strs[i], str) == 0)
            return i;
        i++;
    }
    return -1;
}

int strtabsize(char **strs)
{
	int i;

    i = 0;
    while(strs[i])
        i++;
    return i;
}

void strtabfree(char **strs)
{
    int i = 0;
    while(strs[i])
    {
        free(strs[i]);
        i++;
    }
	free(strs);
}