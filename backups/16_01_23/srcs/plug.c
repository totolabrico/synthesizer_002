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

plug *plug_new(void *addr, int outid, int outchn, int inid, char *meth)
{
    synth *s;
    plug *p;
    void *out;
    void *in;
    void (*f)(void*, double);

    s = (synth*)addr;

    out = lstget_byid(s->osclst, outid)->content;
    if (inid >= 1000)
        in = &s->out[inid - 1000];
    else
        in = lstget_byid(s->osclst, inid)->content;
    f = method_getaddr(meth);
    p = malloc(sizeof(plug));
    p->out = out;
    p->chn = outchn;
    p->in = in;
    p->f = f;
    p->inid = inid;
    p->outid = outid;
    p->plugged = 1;
    return p;
}

void plug_print(int id, void *addr)
{
    plug *p;

    p = (plug*)addr;
    char str[][5]= {"out", "chn", "in"};
    int value[] = {p->outid, p->chn, p->inid};
    printf("\t[%d]", id);
    for (int i =0; i < 3; i++)
    {
       printf("\t%s: %d", str[i], value[i]);
       if (i == 0 || i == 1)
        printf("\t");
    }
    printf("\tmethod: %s\n\v", method_getname(p->f));
}


void plug_clear(void *addr)
{
    plug *p;

    p = (plug*)addr;
    free(p);
}

void plug_transfer(void *addr)
{
    plug *p;
    oscillo *osc;
    double value;

    p  = (plug*)addr;
    if (p->plugged == 1)
    {
        osc = (oscillo *)p->out;
        value = oscillo_getvalue(osc, p->chn);
        p->f(p->in, value);
    }
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
