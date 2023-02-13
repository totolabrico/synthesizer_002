#include "main.h"

void osclst_add(void *addr, double freq, double amp, double pan, double gain)
{
    synth *s;

    s = (synth*)addr;
    lstadd_back(&s->osclst, lstnew(oscillo_new(freq, amp, pan, gain)));
}

void osclst_set(void *addr, int id, char *meth, double value)
{    
    synth *s;
    oscillo *osc;
    void (*f)(void*, double);

    s = (synth*)addr;
    if(id < 0 || id >= lstsize(s->osclst))
        return;
    osc = lstget_byid(s->osclst, id)->content;
    f = method_getaddr(meth);
    if (!f)
        return;
    f(osc, value);
}

void pluglst_add(void *addr, int outid, int outchn, int inid, char *meth)
{
    synth *s;
    int idmax;

    s = (synth*)addr;
    idmax = lstsize(s->osclst);
    if(outid >= 0 && outid < idmax
        && ((inid >= 0 && inid < idmax)
        || (inid - 1000 >= 0 && inid - 1000 < channels))
        && outchn >= 0 && outchn < channels 
        && method_getaddr(meth))
        lstadd_back(&s->pluglst, lstnew(plug_new(addr, outid, outchn, inid, meth)));
}

void pluglst_unplug(void *addr, int id)
{
    synth *s;
    t_list *l;
    plug *p;

    s = (synth*)addr;
    l = lstget_byid(s->pluglst, id);
    if (l)
    {
        p = (plug*)l->content;
        plug_setplugged(p, 0);
    }
}

void pluglst_purge(void *addr)
{
    synth *s;
    t_list **lst;
    t_list *l;
    int i;

    s = (synth*)addr;
    lst = &s->pluglst;
    l = *lst;
    i = 0;
    while (l)
    {   
        if(plug_getplugged((plug*)l->content) == 0)
        {
            *lst = lstpop(*lst, &plug_clear, i);
            l = *lst;
            i = 0;
            synth_print(s);
        }
        else
        {
            l = l->next;
            i++;
        }
    }
}