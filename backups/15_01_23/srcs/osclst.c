#include "main.h"

void osclst_add(void *addr, double freq, double amp, double pan, double gain)
{
    synth *s;

    s = (synth*)addr;
    lstadd_back(&s->osclst, lstnew(oscillo_new(freq, amp, pan, gain)));
}

oscillo *osclst_get(void *addr, int id)
{
    synth *s;
    t_list *l;

    s = (synth*)addr;
    l = lstget(s->osclst, id);
    if (!l || !l->content)
        return NULL;
    return (oscillo*)l->content;
}

void pluglst_add(void *addr, void *out, int chn, void *in, void (*f)(void*, double))
{
    synth *s;

    s = (synth*)addr;
    lstadd_back(&s->pluglst, lstnew(plug_new(out, chn, in, f)));
}