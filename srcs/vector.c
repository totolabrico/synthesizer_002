#include "main.h"

vector *vector_new(float x, float y)
{
    vector *v;
    v = malloc(sizeof(vector));
    if (!v)
        return NULL;
    v->x = x;
    v->y = y;
    return v;
}

void vector_clear(void *addr)
{
    vector *v;

    v = (vector *) addr;
    free(v);
}

void vector_setscalar(vector *vect, char axe, float value)
{
    if (axe == 'x')
        vect->x = value;
    else
        vect->y = value;
}

void vector_mult(vector *vect, float value)
{
    vect->x *= value;
    vect->y *= value;
}

float vector_getbetweenvalue(int i, int len, vector a, vector b)
{
    float w;
    float h;
    float x;
    float y;

    a.x *= len;
    b.x *= len;
    w = b.x - a.x;
    h = b.y - a.y; // abs?
    x = i - a.x;
    y = (x * h) / w + a.y;
    return (y);
}