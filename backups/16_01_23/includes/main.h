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
#include "str_utils.h"
#include <pthread.h>

typedef struct s_plug
{
    void *out;
    int chn;
    void *in;
    void (*f)(void*, double);
    int outid;
    int inid;
    int plugged;
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

typedef struct s_synth_method {
    const char *name;
    void (*f)(void *addr, double value);
} synth_method;

snd_pcm_sframes_t buffer_size;
snd_pcm_sframes_t period_size;

void synth_init(synth *s);
void synth_run(void *synth);
double synth_getchannel(void *addr, int chn);
void synth_generate(const snd_pcm_channel_area_t *areas, void* synth);
void synth_print(void *addr);

void addvalue(void *dest, double value);
void copyvalue(void *addr, double value);

void *oscillo_new(double freq, double amp, double pan, double gain);
void oscillo_setfreq(void* addr, double value);
void oscillo_setamp(void *addr, double value);
void oscillo_setpan(void *addr, double value);
void oscillo_setgain(void *addr, double value);

void oscillo_incphase(void* addr);
double oscillo_getvalue(void* addr, int chn);
void oscillo_print(int id, void *addr);
void oscillo_clear(void *addr);

plug *plug_new(void *addr, int outid, int outchn, int inid, char *meth);
void plug_transfer(void *addr);
void plug_clear(void *addr);
void plug_print(int id, void *addr);
void plug_setplugged(void *addr, int value);
int plug_getplugged(void *addr);

void osclst_add(void *addr, double freq, double amp, double pan, double gain);
void osclst_set(void *addr, int id, char *meth, double value);
void pluglst_add(void *addr, int outid, int outchn, int inid, char *meth);
void pluglst_unplug(void *addr, int id);
void pluglst_purge(void *addr);

void *method_getaddr(char *name);
const char *method_getname(void *addr);

void *prompt(void *addr);

void red();
void blue();
void green();
void white();
void backred();
void backblack();

int format_bits;
unsigned int maxval;
int bps;

#endif