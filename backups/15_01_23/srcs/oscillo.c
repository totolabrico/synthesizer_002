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

void oscillo_setfreq(void *addr, double value)
{
    oscillo *osc;

    osc = (oscillo*)addr;
    osc->freq = value;
    osc->step = max_phase * value / (double)rate;
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