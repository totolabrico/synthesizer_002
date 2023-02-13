#include "main.h"

synth *loadsynth(char *src)
{
    synth *s; 
    int fd;
    char *line;
    
    s = synth_new();
    fd = open(src, O_RDONLY);
    line = get_next_line(fd);
    while(line)
    {
        prompt_analyse(s, line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
    close(fd);
    return s;
}

/*
    for (int i =0; i < 11; i++)
        osclst_add(&s, 0, 0, 0, 0);
    osclst_addplug(&s, 10, 0, 1000, "add");
    osclst_addplug(&s, 10, 1, 1001, "add");
    osclst_set(&s, 10, "freq", 100);
    osclst_set(&s, 10, "amp", 0.5);
    adsr_setpos(&s, 2, 'x', 0.5);
*/
