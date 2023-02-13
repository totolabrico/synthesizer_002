#ifndef PCM_UTILS_H
#define PCM_UTILS_H
#define format SND_PCM_FORMAT_S16
#define rate 44100
#define resample 1
#define device "plughw:1,0"
#define channels 2
#define max_phase 2 * M_PI

int write_loop(snd_pcm_t *handle,
                signed short *samples,
                snd_pcm_channel_area_t *areas,
                void* master);
int xrun_recovery(snd_pcm_t *handle, int err);
int set_hwparams(snd_pcm_t *handle,
                snd_pcm_hw_params_t *params,
                snd_pcm_access_t access,
                unsigned int *buffer_time,
                unsigned int *period_time);
int set_swparams(snd_pcm_t *handle,
                snd_pcm_sw_params_t *swparams);
void *pcm_start(void* master);

struct async_private_data {
    signed short *samples;
    snd_pcm_channel_area_t *areas;
    double phase;
};
struct transfer_method {
    const char *name;
    snd_pcm_access_t access;
    int (*transfer_loop)(snd_pcm_t *handle,
                 signed short *samples,
                 snd_pcm_channel_area_t *areas,
                 void* master);
};

#endif