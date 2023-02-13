#include "main.h"

void prompt_analyse(synth *s, char *cmd)
{
    char **args;
    int cmdsize;

    if(ft_strlen(cmd) == 1)
        return;
    cmd[ft_strlen(cmd) - 1] = 0;
    args = ft_split(cmd, ' ');
    cmdsize = strtabsize(args);
    //printf("%d\n", cmdsize);
    if(strcmp(args[0], "unplug") == 0 && cmdsize == 2)
        pluglst_unplug(s, atoi(args[1]));
    else if(strcmp(args[0], "plug") == 0 && cmdsize == 5)
        pluglst_add(s, atoi(args[1]), atoi(args[2]), atoi(args[3]), args[4]);
    else if(cmdsize == 3)
        osclst_set(s, atoi(args[0]), args[1], atof(args[2]));
    strtabfree(args);
}

void *prompt(void *addr)
{
    synth *s;
    char buffer[100];

    s = (synth*)addr;

    pluglst_add(s, 0, 0, 1000, "add");
    pluglst_add(s, 0, 1, 1001, "add");
    //osclst_set(s, 0, "freq", 100);
    //osclst_set(s, 0, "amp", 0.1);*/
    synth_print(s);

    white();

    while(1)
    {
        read(0, &buffer, 1000);
        system("clear");
        prompt_analyse(s, buffer);
        synth_print(s);
    }
    return NULL;
}