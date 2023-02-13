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

void osclst_addplug(void *addr, int srcid, int srcchn, int destid, char *method)
{
    synth *s;
    oscillo *osc;
    t_list **pluglst;
    void *dest;

    s = (synth*)addr;
    osc = (oscillo*)lstget_byid(s->osclst, srcid)->content; 
    pluglst = (t_list **)&osc->pluglst[srcchn];
    if (destid >=1000)
        dest = &s->out[destid - 1000];
    else
        dest = lstget_byid(s->osclst, destid)->content;
    lstadd_back(pluglst, lstnew(plug_new(dest, method)));
}

void osclst_unplug(void *addr, int srcid, int srcchn, int plugid)
{
    synth *s;
    oscillo *osc;

    s = (synth*)addr;
    osc = (oscillo*)lstget_byid(s->osclst, srcid)->content; 
    pluglst_unplug(osc->pluglst[srcchn], plugid);
}

