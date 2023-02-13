#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <getopt.h>
#include "/usr/include/alsa/asoundlib.h"
#include <sys/time.h>
#include <math.h>
#include "pcm_utils.h"
#include "list_utils.h"

typedef struct s_plug
{
    void *src;
    int chn;
    void *dest;
    void (*f)(void*, double);
} plug;

typedef struct s_oscillo
{
    double freq;
    double amp;
    double pan;
    double gain;
    double phase;
    double step;
} oscillo;

typedef struct s_synth
{
    double out[channels];
    t_list *osclst;
    t_list *pluglst;
} synth;

snd_pcm_sframes_t buffer_size;
snd_pcm_sframes_t period_size;

void synth_init(synth *s);
void synth_run(void *synth);
double synth_getchannel(void *addr, int chn);
void synth_generate(const snd_pcm_channel_area_t *areas, void* synth);

void addvalue(void *dest, double value);
void copyvalue(void *addr, double value);

void *oscillo_new(double freq, double amp, double pan, double gain);
void oscillo_setfreq(void* addr, double freq);
void oscillo_incphase(void* addr);
double oscillo_getvalue(void* addr, int chn);

void osclst_add(void *addr, double freq, double amp, double pan, double gain);
oscillo *osclst_get(void *addr, int id);
void pluglst_add(void *addr, void *out, int chn, void *in, void (*f)(void*, double));
plug *plug_new(void *src, int chn, void *dest, void (*f)(void*, double));
void plug_transfer(void *addr);

int format_bits;
unsigned int maxval;
int bps;

#endif