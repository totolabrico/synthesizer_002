#include "main.h"

void copyvalue(void *addr, double value)
{
    double *v;

    v = (double*)addr;
    *v = value;
}

void addvalue(void *dest, double value)
{
    double *v;

    v = (double *)dest;
    *v += value;
}

plug *plug_new(void *dest, char *method)
{
    plug *p;

    p = malloc(sizeof(plug));
    p->dest = dest;
    p->method = method_getaddr(method);
    p->plugged = 1;
    return p;
}

void plug_print(void *addr, plug *p, int id)
{
    synth* s;
    int destid;

    s = (synth*)addr;
    printf("\t[plug:%d]->",id);
    if (p->dest == &s->out[0])
        printf("master-0");
    else if (p->dest == &s->out[1])
        printf("master-1");
    else
    {
        destid = lstgetid_byaddr(s->osclst, p->dest);
        printf("%d-%s", destid, method_getname(p->method));
    }
}

void plug_clear(void *addr)
{
    plug *p;

    p = (plug*)addr;
    free(p);
}

void plug_setplugged(void *addr, int value)
{
    plug *p;

    p  = (plug*)addr;
    p->plugged = value;
}

int plug_getplugged(void *addr)
{
    plug *p;

    p  = (plug*)addr;
    return p->plugged;
}
