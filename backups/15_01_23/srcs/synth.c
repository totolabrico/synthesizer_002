#include "main.h"

void synth_init(synth *s)
{
    s->out[0] = 0;
    s->out[1] = 0;
    s->osclst = NULL;
    s->pluglst = NULL;
}

void synth_run(void *addr)
{
    synth *s;

    s = (synth*)addr;
    s->out[0] = 0;
    s->out[1] = 0;
    lstiter(s->pluglst, &plug_transfer);
    lstiter(s->osclst, &oscillo_incphase);
}

double synth_getchannel(void *addr, int chn)
{
    synth *s;

    s = (synth*)addr;
    return s->out[chn] *maxval;
}

void synth_generate(const snd_pcm_channel_area_t *areas, void* synth)
{
    unsigned char *samples[channels];
    int steps[channels];
    unsigned int chn;
    int count = period_size;

    /* verify and prepare the contents of areas */
    for (chn = 0; chn < channels; chn++) {
        if ((areas[chn].first % 8) != 0) {
            printf("areas[%u].first == %u, aborting...\n", chn, areas[chn].first);
            exit(EXIT_FAILURE);
        }
        samples[chn] = /*(signed short *)*/(((unsigned char *)areas[chn].addr) + (areas[chn].first / 8));
        if ((areas[chn].step % 16) != 0) {
            printf("areas[%u].step == %u, aborting...\n", chn, areas[chn].step);
            exit(EXIT_FAILURE);
        }
        steps[chn] = areas[chn].step / 8;
    }
    while (count-- > 0) {
        int res, i;
        synth_run(synth);
        for (chn = 0; chn < channels; chn++)
        {
            res = synth_getchannel(synth, chn);
            for (i = 0; i < bps; i++)
                *(samples[chn] + i) = (res >>  i * 8) & 0xff;
            samples[chn] += steps[chn];
        }
    }
}