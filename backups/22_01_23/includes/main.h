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
#include "get_next_line.h"
#include <pthread.h>

typedef struct s_vector
{
    float x;
    float y;
} vector;


typedef struct s_adsr
{
    int len;
    int x;
    vector vectors[5];
    t_list *pluglst;
} adsr;

typedef struct s_plug
{
    void *dest;
    void (*method)(void*, double);
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
    t_list *pluglst[2];
} oscillo;

typedef struct s_synth
{
    double out[channels];
    adsr adsr;
    t_list *osclst;
    //t_list *pluglst;
} synth;

typedef struct s_synth_method {
    const char *name;
    void (*f)(void *addr, double value);
} synth_method;

snd_pcm_sframes_t buffer_size;
snd_pcm_sframes_t period_size;

synth *synth_new();
void synth_clear(void *addr);
void synth_run(void *synth);
double synth_getchannel(void *addr, int chn);
void synth_generate(const snd_pcm_channel_area_t *areas, void* synth);
void synth_print(void *addr);

synth *loadsynth(char *src);
void prompt_analyse(synth *s, char *cmd);


void addvalue(void *dest, double value);
void copyvalue(void *addr, double value);

void *oscillo_new(double freq, double amp, double pan, double gain);
void oscillo_setfreq(void* addr, double value);
void oscillo_setamp(void *addr, double value);
void oscillo_setpan(void *addr, double value);
void oscillo_setgain(void *addr, double value);
void oscillo_incphase(void* addr);
double oscillo_getvalue(oscillo *osc, int chn);
void oscillo_print(void *addr, int id);
void oscillo_clear(void *addr);
void oscillo_write(void *addr);
void oscillo_plugpurge(void *addr);

plug *plug_new(void *dest, char *method);
void plug_clear(void *addr);
void plug_print(void *addr, plug *p, int id);
void plug_setplugged(void *addr, int value);
int plug_getplugged(void *addr);

void osclst_add(void *addr, double freq, double amp, double pan, double gain);
void osclst_set(void *addr, int id, char *meth, double value);
void osclst_addplug(void *addr, int srcid, int srcchn, int destid, char *method);
void osclst_unplug(void *addr, int srcid, int srcchn, int plugid);

void adsr_init(adsr *a, float duration);
void adsr_setlen(adsr *a, float duration);
void adsr_setpos(void *addr, int id, char axe, float value);
float adsr_getvalue(void *addr);
int adsr_setx(adsr *a);
int adsr_findvector(adsr *a, int i, int id);

void vector_init(vector *vect, float x, float y);
float vector_getbetweenvalue(int i, int len, vector a, vector b);
void vector_setscalar(vector *vect, char axe, float value);


void pluglst_unplug(t_list *lst, int id);
void pluglst_purge(t_list **lst);
void pluglst_print(void *addr, t_list *lst, int id);

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