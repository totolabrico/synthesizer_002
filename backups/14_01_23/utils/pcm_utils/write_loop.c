#include "main.h"

int write_loop(snd_pcm_t *handle,
              signed short *samples,
              snd_pcm_channel_area_t *areas,
              void *master)
{
    signed short *ptr;
    int err, cptr;
    format_bits = snd_pcm_format_width(format); // 16
    maxval = (1 << (format_bits - 1)) - 1; // 32767
    bps = format_bits / 8;  /* bytes per sample */ // 2

    while (1) {
        generate_master(areas, master);
        ptr = samples;
        cptr = period_size;
        while (cptr > 0) {
            err = snd_pcm_writei(handle, ptr, cptr);
            if (err == -EAGAIN)
                continue;
            if (err < 0) {
                if (xrun_recovery(handle, err) < 0) {
                    printf("Write error: %s\n", snd_strerror(err));
                    exit(EXIT_FAILURE);
                }
                break;  /* skip one period */
            }
            ptr += err * channels;
            cptr -= err;
        }
    }
}