#include "main.h"

int main()
{
    synth s;
    pthread_t threads[2];
    void *threads_methods[] = {&prompt, &pcm_start};
    synth_init(&s);
    for (int i =0; i < 10; i++)
        osclst_add(&s, 0, 0, 0, 0);    
    for (int i = 0; i < 2 ; i++)
        pthread_create(&threads[i], NULL, threads_methods[i], (void*)&s);
    for (int i = 0; i < 2 ; i++)
        pthread_join(threads[i], NULL);
}
