#include "main.h"

int main()
{
    note anote;

    max_phase = 2. * M_PI;
    note_init(&anote, 60);
    pcm_start(&anote);
    return 0;
}
