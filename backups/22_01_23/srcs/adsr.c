#include "main.h"

void adsr_init(adsr *a, float len)
{
    
    vector_init(&a->vectors[0], 0,0);
    vector_init(&a->vectors[1], 0.1,0.8);
    vector_init(&a->vectors[2], 0.2,0.3);
    vector_init(&a->vectors[3], 0.7,0.3);
    vector_init(&a->vectors[4], 1,0);
    adsr_setlen(a, len);
    a->pluglst = NULL;
}


void adsr_setlen(adsr *a, float duration)
{
    a->len = (int)(duration * rate);
}

void adsr_setpos(void *addr, int id, char axe, float value)
{
    synth *s;

    s =(synth*)addr;
    vector_setscalar(&s->adsr.vectors[id], axe, value);
}

int adsr_findvector(adsr *a, int x, int id)
{
    if (id == 3)
        return id;
    if ((float)x >= a->vectors[id].x * a->len && (float)x < a->vectors[id + 1].x * a->len)
        return id;
    return adsr_findvector(a, x, id + 1);
}

int adsr_setx(adsr *a)
{
    int x;

    x = a->x;
    if (x < a->len)
    {
        x++;
        a->x = x;
    }
    return x;
}

float adsr_getvalue(void *addr)
{
    adsr *a;
    int id;
    int len;
    int x;
    float value;

    a = &((synth*)addr)->adsr;
    len = a->len;
    x = a->x;

    if (x < a->vectors[0].x * len || x > a->vectors[4].x * len)
        return 0;
    id = adsr_findvector(a, x, 0);
    value = vector_getbetweenvalue(x, len, a->vectors[id], a->vectors[id +1]);
    //printf("value : %f id: %d\n", value, id);
    //return vector_getbetweenvalue(i, len, a->vectors[id], a->vectors[id +1]);
    return value;
}