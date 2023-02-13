#include "main.h"

void generate_master(const snd_pcm_channel_area_t *areas, void* master)
{
    unsigned char *samples[channels];
    int steps[channels];
    unsigned int chn;
    note *anote;
    anote = (note*)master;

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
    generate_note(samples, steps, anote);
}