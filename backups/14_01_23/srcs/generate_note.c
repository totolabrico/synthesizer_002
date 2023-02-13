#include "main.h"

void generate_note(unsigned char *samples[], int steps[], note* anote)
{
    //double phase = anote->signal[0].phase;
    //double step = max_phase * anote->signal[0].freq / (double)rate;
    unsigned int chn;
    int count = period_size;

    while (count-- > 0) {
        int res, i;
        for (chn = 0; chn < channels; chn++)
        {
            res = note_getvalue(anote, chn);
            for (i = 0; i < bps; i++)
                *(samples[chn] + i) = (res >>  i * 8) & 0xff;
            samples[chn] += steps[chn];
        }
        note_incphase(anote);
    }
}