#include "main.h"

void note_init(note *anote, double freq)
{
    int i = 0;
    while (i < 3)
    {
        oscillo_init(&(anote->signal[i]), freq * (i + 1));
        oscillo_init(&(anote->env[i]), 0.33 * (i + 1));
        oscillo_init(&(anote->pan[i]), 0.33 * (i + 1));
        i++;
    }
}

double note_getpan(int chn, double pan)
{
    pan = (pan + 1) / 2; 
    if (chn == 0)
        return 1 - pan;
    else
        return pan;
}

double note_getvalue(note *anote, int chn)
{
    double res;
    double env;
    double pan;
    unsigned int i;

    res = 0;
    env = 0;
    pan = 0;
    i = 0;
    while(i < 3)
    {
        res += oscillo_getvalue(&(anote->signal[i])) / 3;
        env += oscillo_getvalue(&(anote->env[i])) / 3;
        pan += oscillo_getvalue(&(anote->pan[i])) / 3;
        i++;
    }
    res *= maxval;
    res *= env ;
    pan = note_getpan(chn, pan);
    res *= pan;
    return res;
}

void note_incphase(note *anote)
{
    int i = 0;

    while (i < 3)
    {
        oscillo_incphase(&(anote->signal[i]));
        oscillo_incphase(&(anote->env[i]));
        oscillo_incphase(&(anote->pan[i]));
        i++;
    }
}