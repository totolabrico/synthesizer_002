#include "main.h"

void* oscillo_new(char *cmd)
{
    oscillo *osc;
    char **splited;
    int len;

    osc = malloc(sizeof(oscillo));
    splited = ft_split(cmd, ' ');
    oscillo_setfreq(osc, 0);
    osc->amp = 0;
    osc->gain = 0;
    osc->pan = 0;
    osc->phase = 0;
    len = strtabsize(splited);
    if (len > 0)
        oscillo_setfreq(osc, atof(splited[0]));
    if (len > 1)
       osc->amp = atof(splited[1]);
    if (len > 2)
       osc->pan = atof(splited[2]);
    if (len > 3)
       osc->gain = atof(splited[3]);
    osc->pluglst[0] = NULL;
    osc->pluglst[1] = NULL;
    strtabfree(splited);
    return (void *)osc;
}

void oscillo_clear(void *addr)
{
    oscillo *osc;

    osc = (oscillo*)addr;
    lstclear((t_list **)osc->pluglst[0], &plug_clear);
    lstclear((t_list**)osc->pluglst[1], &plug_clear);
    free(osc);
}

void oscillo_setfreq(void *addr, double value)
{
    oscillo *osc;

    osc = (oscillo*)addr;
    osc->freq = value;
    osc->step = max_phase * value / (double)rate;
}

void oscillo_setamp(void *addr, double value)
{
    oscillo *osc;

    osc = (oscillo*)addr;
    osc->amp = value;
}

void oscillo_setpan(void *addr, double value)
{
    oscillo *osc;

    osc = (oscillo*)addr;
    osc->pan = value;
}

void oscillo_setgain(void *addr, double value)
{
    oscillo *osc;

    osc = (oscillo*)addr;
    osc->gain = value;
}

void oscillo_incphase(void *addr)
{
    oscillo* osc;
    double phase;

    osc = (oscillo*)addr;
    phase = osc->phase;
    phase += osc->step;
    if (phase >= max_phase)
        phase -= max_phase;
    osc->phase = phase;
}

double oscillo_getpan(double pan, int chn)
{
    pan = (pan + 1) / 2; 
    if (chn == 0)
        return 1 - pan;
    else
        return pan;
}

double oscillo_getvalue(oscillo *osc, int chn)
{
    return (sin(osc->phase) * osc->amp + osc->gain) * oscillo_getpan(osc->pan, chn);
}

void oscillo_write(void *addr)
{
    oscillo* osc;
    double value;
    int i;

    osc = (oscillo*)addr;
    i = 0;
    while (i < 2)
    {
        value = oscillo_getvalue(osc, i);
        pluglst_write(osc->pluglst[i], value);
        i++;
    }
    oscillo_incphase(addr);
    oscillo_plugpurge(addr);
}

void oscillo_plugpurge(void *addr)
{
    oscillo* osc;
    int chn;

    osc = (oscillo*)addr;
    chn = 0;
    while (chn < 2)
    {
        pluglst_purge((t_list**)&osc->pluglst[chn]);
        chn++;
    }
}

void oscillo_print(void *addr, int id)
{
    synth* s;
    oscillo* osc;
    char str[][5]= {"f", "a", "p", "g"};

    s = (synth*)addr;
    osc = (oscillo*)lstget_byid(s->osclst, id)->content;
    double value[] = {osc->freq, osc->amp, osc->pan, osc->gain};
    white();
    printf("\t[%d]", id);
    for (int i =0; i < 4; i++)
        printf("\t%s: %f", str[i], value[i]);
    blue();
    printf("\n\t");
    pluglst_print(addr, osc->pluglst[0], 0);
    printf("\n\t");
    pluglst_print(addr, osc->pluglst[1], 1);
    printf("\n");
}