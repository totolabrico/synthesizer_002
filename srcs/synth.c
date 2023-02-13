#include "main.h"

synth *synth_new()
{
    synth *s;

    s = malloc(sizeof(synth));
    s->out[0] = 0;
    s->out[1] = 0;
    s->osclst = NULL;
    s->lineslst = NULL;
    return s;
}

void synth_clear(void *addr)
{
    synth *s;

    s = (synth *)addr;
    lstclear(&s->osclst, &oscillo_clear);
    free(s);
}

void synth_run(void *addr)
{
    synth *s;

    s = (synth*)addr;
    s->out[0] = 0;
    s->out[1] = 0;
    lstiter(s->osclst, &oscillo_write);
    lstiter(s->lineslst, &lines_write);
}

double synth_getchannel(void *addr, int chn)
{
    synth *s;

    s = (synth*)addr;
    return s->out[chn] * maxval;
}

void synth_generate(const snd_pcm_channel_area_t *areas, void* s)
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
        synth_run(s);
        for (chn = 0; chn < channels; chn++)
        {
            res = synth_getchannel(s, chn);
            for (i = 0; i < bps; i++)
                *(samples[chn] + i) = (res >>  i * 8) & 0xff;
            samples[chn] += steps[chn];
        }
    }
}