#include "main.h"

int main()
{
    synth s;

    synth_init(&s);

    osclst_add(&s, 220,0.1, 0, 0);
    osclst_add(&s, 1, 0.1, 0, 0);
    osclst_add(&s, 0.1, 40, 0, 80);
    osclst_add(&s, 0.1, 1, 0, 0);

    pluglst_add(&s, osclst_get(&s, 0), 0, &s.out[0], &addvalue);
    pluglst_add(&s, osclst_get(&s, 0), 1, &s.out[1], &addvalue);
    pluglst_add(&s, osclst_get(&s, 2), 0, osclst_get(&s, 0), &oscillo_setfreq);
    pluglst_add(&s, osclst_get(&s, 1), 0, &osclst_get(&s, 0)->amp, &copyvalue);
    pluglst_add(&s, osclst_get(&s, 3), 0, &osclst_get(&s, 0)->pan, &copyvalue);
    
    pcm_start(&s);
}
