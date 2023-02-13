#include "main.h"

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

void osclst_unplug(void *addr, int srcid, int srcchn, int plugid)
{
    synth *s;
    oscillo *osc;

    s = (synth*)addr;
    osc = (oscillo*)lstget_byid(s->osclst, srcid)->content; 
    pluglst_unplug(osc->pluglst[srcchn], plugid);
}

