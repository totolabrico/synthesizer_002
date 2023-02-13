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

    if(strcmp(args[0], "osc") == 0)
        lstadd_back(&s->osclst, lstnew(oscillo_new(&cmd[4])));
    else if(strcmp(args[0], "lines") == 0)
        lstadd_back(&s->lineslst, lstnew(lines_new(&cmd[6])));
    else if(strcmp(args[0], "plug") == 0)
        synth_addplug(s, &cmd[5]);
    /*
    else if(strcmp(args[0], "unplug") == 0 && cmdsize == 4)
        osclst_unplug(s, atoi(args[1]), atoi(args[2]), atoi(args[3]));
    else if(cmdsize == 3)
        osclst_set(s, atoi(args[0]), args[1], atof(args[2]));
    */
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