#ifndef STRUCT_H
#define STRUCT_H
#include "main.h"

typedef struct s_plug
{
    void *dest;
    void (*method)(void*, double);
    int plugged;
} plug;

typedef struct s_vector
{
    float x;
    float y;
} vector;

typedef struct s_lines
{
    int len;
    int x;
    t_list *vectorlst;
    t_list *pluglst;
} lines;

typedef struct s_oscillo
{
    double freq;
    double amp;
    double pan;
    double gain;
    double phase;
    double step;
    t_list *pluglst[2];
} oscillo;

typedef struct s_synth
{
    double out[channels];
    t_list *lineslst;
    t_list *osclst;
    //t_list *pluglst;
} synth;

typedef struct s_synth_method {
    const char *name;
    void (*f)(void *addr, double value);
} synth_method;

#endif