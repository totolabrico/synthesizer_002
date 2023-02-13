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

typedef struct s_oscillo
{
    double freq;
    double phase;
    double step;
} oscillo;

typedef struct t_note
{
    oscillo signal[3];
    oscillo env[3];
    oscillo pan[3];
} note;

snd_pcm_sframes_t buffer_size;
snd_pcm_sframes_t period_size;

void generate_master(const snd_pcm_channel_area_t *areas, void* master);
void generate_note(unsigned char *samples[], int steps[], note* anote);

void note_init(note *anote, double freq);
double note_getvalue(note *anote, int chn);
void note_incphase(note *anote);

void oscillo_init(oscillo *osc, double freq);
void oscillo_setfreq(oscillo *osc, double freq);
void oscillo_incphase(oscillo *osc);
double oscillo_getvalue(oscillo *osc);

int format_bits;
unsigned int maxval;
int bps;
double max_phase;

#endif