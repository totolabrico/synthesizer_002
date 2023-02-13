#include "main.h"

void* oscillo_new(double freq, double amp, double pan, double gain)
{
    oscillo *osc;

    osc = malloc(sizeof(oscillo));
    oscillo_setfreq(osc, freq);
    osc->amp =amp;
    osc->gain = gain;
    osc->phase = 0;
    osc->pan = pan;
    return (void *)osc;
}

void oscillo_clear(void *addr)
{
    oscillo *osc;

    osc = (oscillo*)addr;
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

double oscillo_getvalue(void *addr, int chn)
{
    oscillo* osc;
    double value;
    double gain;

    osc = (oscillo*)addr;
    value = sin(osc->phase) * osc->amp * oscillo_getpan(osc->pan, chn);
    gain = osc->gain;
    return value + gain;
}

void oscillo_print(int id, void *addr)
{
    oscillo* osc;
    char str[][5]= {"f", "a", "p", "g"};
    osc = (oscillo*)addr;
    double value[] = {osc->freq, osc->amp, osc->pan, osc->gain};
    printf("\t[%d]", id);
    for (int i =0; i < 4; i++)
        printf("\t%s: %f", str[i], value[i]);
    printf("\n\v");
}