#include "main.h"

void synth_print(void *addr)
{
    synth *s;
    t_list *l;
    int i;

    s = (synth*)addr;
    l = s->osclst;
    i = 0;
    white();
    printf("\vsinoto_002\v\n");
    green();
    printf("\toscillators\n\v");
    while (l)
    {
        oscillo_print(i, l->content);
        l = l->next;
        i++;
    }
    printf("\v");
    l = s->pluglst;
    i = 0;
    
    blue();
    printf("\tplugs\n\v");
    while (l)
    {
        plug_print(i, l->content);
        l = l->next;
        i++;
    }
    printf("\v");
}

void red()
{
    printf("\033[0;31m"); 
}

void blue()
{
    printf("\033[0;34m");
}

void green()
{
    printf("\033[0;32m");
}

void white()
{
    printf("\033[0;37m");
}

void backred()
{
    printf("\033[0;41m"); 
}

void backblack()
{
    printf("\033[0;40m"); 
}