#include "main.h"

synth_method synth_methods[] =
{
    {"add", &addvalue},
    {"freq", &oscillo_setfreq},
    {"amp", &oscillo_setamp},
    {"pan", &oscillo_setpan},
    {"gain", &oscillo_setgain}
};

void *method_getaddr(char *name)
{
    int size;
    int i;

    size = sizeof(synth_methods) / sizeof(synth_methods[0]);
    i = 0;
    while (i < size)
    {
    if (strcmp(name, synth_methods[i].name) == 0)
        return synth_methods[i].f;
    i++;
    }
    return NULL;
}

const char *method_getname(void *addr)
{
    int size;
    int i;

    size = sizeof(synth_methods) / sizeof(synth_methods[0]);
    i = 0;
    while (i < size)
    {
    if (synth_methods[i].f == addr)
        return synth_methods[i].name;
    i++;
    }
    return "nomethod";
}
