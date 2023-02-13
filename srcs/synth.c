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

t_list **synth_getplugsrc(synth *s, char *name, int id, int chn)
{
    t_list **lst;
    oscillo *osc;
    lines *l;
    
    if(strcmp(name, "osc") == 0)
    {
        osc = (oscillo*)lstget_byid(s->osclst, id)->content; 
        lst = (t_list **)&osc->pluglst[chn];
    }
    else if (strcmp(name, "lines"))
    {
        l = (lines*)lstget_byid(s->lineslst, id)->content;
        lst = (t_list **)l->pluglst;
    }
    return lst;
}

void *synth_getplugdest(synth *s, char *dest, int id)
{
    if (strcmp(dest, "master") == 0)
        return &s->out[id];
    else if (strcmp(dest, "osc") == 0)
        return lstget_byid(s->osclst, id)->content;
    else if (strcmp(dest, "lines") == 0)
        return lstget_byid(s->lineslst, id)->content;
    return NULL;
}

void synth_addplug(synth *s, char *cmd)
{
    char **splited;
    void *src;
    void *dest;
    char *meth;

    splited = ft_split(cmd, ' ');
    if(strtabsize(splited) != 6)
        return;
    meth = splited[5];
    if(!method_getaddr(meth))
        return;
    src = synth_getplugsrc(s, splited[0], atoi(splited[1]), atoi(splited[2]));
    dest = synth_getplugdest(s, splited[3], atoi(splited[4]));
    lstadd_back(src, lstnew(plug_new(dest, meth)));
}

void synth_run(void *addr)
{
    synth *s;

    s = (synth*)addr;
    s->out[0] = 0;
    s->out[1] = 0;
    lstiter(s->osclst, &oscillo_write);
    lstiter(s->lineslst, &lines_write);
    lstpurgenull(&s->lineslst, &lines_clear);
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