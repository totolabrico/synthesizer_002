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
    printf("%s %d \n", args[3], cmdsize);

    if(strcmp(args[0], "osc") == 0 && cmdsize == 5)
        osclst_add(s, atof(args[1]), atof(args[2]), atof(args[3]), atof(args[4]));
    else if(strcmp(args[0], "unplug") == 0 && cmdsize == 4)
        osclst_unplug(s, atoi(args[1]), atoi(args[2]), atoi(args[3]));
    else if(strcmp(args[0], "plug") == 0 && cmdsize == 5)
    { 
        if(strcmp(args[3], "master")== 0)
            osclst_addplug(s, atoi(args[1]), atoi(args[2]), 1000+atoi(args[4]), "add");
        else
            osclst_addplug(s, atoi(args[1]), atoi(args[2]), atoi(args[3]), args[4]);
    }
    else if(cmdsize == 3)
        osclst_set(s, atoi(args[0]), args[1], atof(args[2]));
    strtabfree(args);
}

void *prompt(void *addr)
{
    synth *s;
    char buffer[100];

    s = (synth*)addr;
    //osclst_set(s, 0, "freq", 100);
    //synth_print(s);
    white();
    while(1)
    {
        read(0, &buffer, 1000);
        //system("clear");
        prompt_analyse(s, buffer);
        //synth_print(s);
    }
    return NULL;
}