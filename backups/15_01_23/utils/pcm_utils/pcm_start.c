#include "main.h"

unsigned int buffer_time = 500000;       /* ring buffer length in us */
unsigned int period_time = 100000;       /* period time in us */
snd_output_t *output = NULL;

int pcm_start(void *master)
   {
   struct transfer_method transfer_methods[] = 
    {
    { "write", SND_PCM_ACCESS_RW_INTERLEAVED, write_loop },
    { NULL, SND_PCM_ACCESS_RW_INTERLEAVED, NULL }
    };

    snd_pcm_t *handle;
    int err;
    snd_pcm_hw_params_t *hwparams;
    snd_pcm_sw_params_t *swparams;
    int method = 0;
    signed short *samples;
    unsigned int chn;
    snd_pcm_channel_area_t *areas;

    snd_pcm_hw_params_alloca(&hwparams);
    snd_pcm_sw_params_alloca(&swparams);

    err = snd_output_stdio_attach(&output, stdout, 0);
    if (err < 0) {
        printf("Output failed: %s\n", snd_strerror(err));
        return 0;
    }

    printf("Playback device is %s\n", device);
    printf("Stream parameters are %uHz, %s, %u channels\n", rate, snd_pcm_format_name(format), channels);
    printf("Using transfer method: %s\n", transfer_methods[method].name);

    if ((err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        printf("Playback open error: %s\n", snd_strerror(err));
        return 0;
    }

    if ((err = set_hwparams(handle, hwparams, transfer_methods[method].access, &buffer_time, &period_time)) < 0) {
        printf("Setting of hwparams failed: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }
    if ((err = set_swparams(handle, swparams)) < 0) {
        printf("Setting of swparams failed: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    samples = malloc((period_size * channels * snd_pcm_format_physical_width(format)) / 8);
    if (samples == NULL) {
        printf("No enough memory\n");
        exit(EXIT_FAILURE);
    }

    areas = calloc(channels, sizeof(snd_pcm_channel_area_t));
    if (areas == NULL) {
        printf("No enough memory\n");
        exit(EXIT_FAILURE);
    }
    for (chn = 0; chn < channels; chn++) {
        areas[chn].addr = samples;
        areas[chn].first = chn * snd_pcm_format_physical_width(format);
        areas[chn].step = channels * snd_pcm_format_physical_width(format);
    }

    err = transfer_methods[method].transfer_loop(handle, samples, areas, master);
    if (err < 0)
        printf("Transfer failed: %s\n", snd_strerror(err));

    free(areas);
    free(samples);
    snd_pcm_close(handle);
    return 0;
   }