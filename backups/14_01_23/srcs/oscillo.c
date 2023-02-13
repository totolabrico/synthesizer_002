#include "main.h"

void oscillo_init(oscillo *osc, double freq)
{
    oscillo_setfreq(osc, freq);
    osc->phase = 0;
}

void oscillo_setfreq(oscillo *osc, double freq)
{
    osc->freq = freq;
    osc->step = max_phase * osc->freq / (double)rate;
}

void oscillo_incphase(oscillo *osc)
{
    double phase;

    phase = osc->phase;
    phase += osc->step;
    if (phase >= max_phase)
        phase -= max_phase;
    osc->phase = phase;
}

double oscillo_getvalue(oscillo *osc)
{
    return sin(osc->phase);
}