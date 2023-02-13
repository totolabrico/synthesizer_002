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

plug *plug_new(void *src, int chn, void *dest, void (*f)(void*, double))
{
    plug *p;

    p = malloc(sizeof(plug));
    p->src = src;
    p->chn = chn;
    p->dest = dest;
    p->f = f;
    return p;
}

void plug_transfer(void *addr)
{
    plug *p;
    oscillo *osc;
    double value;

    p  = (plug*)addr;
    osc = (oscillo *)p->src;
    value = oscillo_getvalue(osc, p->chn);
    p->f(p->dest, value);
}