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
#include "colors.h"
#include "struct.h"
#define device "plughw:0,0"

snd_pcm_sframes_t buffer_size;
snd_pcm_sframes_t period_size;
int format_bits;
unsigned int maxval;
int bps;

synth *synth_new();
void synth_clear(void *addr);
void synth_run(void *synth);
double synth_getchannel(void *addr, int chn);
void synth_generate(const snd_pcm_channel_area_t *areas, void* synth);
void synth_addplug(synth *s, char *cmd);
void synth_print(void *addr);

synth *loadsynth(char *src);
void *prompt(void *addr);
void prompt_analyse(synth *s, char *cmd);

void *method_getaddr(char *name);
const char *method_getname(void *addr);

void addvalue(void *dest, double value);
void copyvalue(void *addr, double value);

void* oscillo_new(char *cmd);
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

vector *vector_new(float x, float y);
void vector_clear(void *addr);
float vector_getbetweenvalue(int i, int len, vector a, vector b);
void vector_setscalar(vector *vect, char axe, float value);

lines *lines_new(char *cmd);
void lines_clear(void *addr);
void lines_addvectors(lines *l, char *cmd);
void lines_setlen(lines *l);
void lines_setpos(lines *l, int id, char axe, float value);
int lines_setx(lines *l);
int lines_findvector(lines *l, int i, int id);
float lines_getvalue(lines *l);
void lines_write(void *addr);
void lines_plugpurge(void *addr);

void osclst_set(void *addr, int id, char *meth, double value);
void osclst_unplug(void *addr, int srcid, int srcchn, int plugid);

void pluglst_write(t_list *lst, double value);
void pluglst_unplug(t_list *lst, int id);
void pluglst_purge(t_list **lst);
void pluglst_print(void *addr, t_list *lst, int id);

#endif