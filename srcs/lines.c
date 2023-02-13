#include "main.h"

lines *lines_new(char *cmd)
{
    lines *l;
    l = malloc(sizeof(lines));
    if(!l)
        return NULL;
    l->vectorlst = NULL;
    l->pluglst = NULL;
    lines_addvectors(l, cmd);
    lines_setlen(l);
    return l;
}

void lines_clear(void *addr)
{
    lines *l;

    l = (lines*)addr;
    lstclear((t_list **)l->vectorlst, &vector_clear);
    lstclear((t_list**)l->pluglst, &plug_clear);
    free(l);
}

void lines_addvectors(lines *l, char *cmd)
{
    char **splited = ft_split(cmd, ' ');
    int i;
    int len;
    t_list *lst;

    len = strtabsize(splited);
    if (!splited || len % 2 != 0)
        return;
    lst = l->vectorlst;
    i = 0;
    while(i < len)
    {
        lstadd_back(&lst, lstnew(vector_new(atof(splited[i]), atof(splited[i + 1]))));
        i += 2;
    }
    strtabfree(splited);
}

void lines_setlen(lines *l)
{
    t_list *last;
    vector *v;

    last = lstlast(l->vectorlst)->content;
    if(!last)
        return;
    v  = (vector *)last;
    l->len = v->x * rate;
}

vector *lines_getvector(lines *l, int id)
{
    t_list *lst;
    vector *v;

    lst = l->vectorlst;
    v = (vector *)lstget_byid(lst, id)->content;
    return v;
}

void lines_setpos(lines *l, int id, char axe, float value)
{
    vector_setscalar(lines_getvector(l, id), axe, value);
}

int lines_findvector(lines *l, int x, int id)
{
    int len;
    
    len = l->len;
    if (id == lstsize(l->vectorlst) - 1)
        return id;
    if ((float)x >= lines_getvector(l, id)->x * len && 
        (float)x < lines_getvector(l, id + 1)->x * len)
        return id;
    return lines_findvector(l, x, id + 1);
}

int lines_setx(lines *a)
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

float lines_getvalue(lines *l)
{
    int id;
    int len;
    int x;
    float value;

    len = l->len;
    x = l->x;
    if (x < lines_getvector(l, 0)->x * len || x > lines_getvector(l, lstsize(l->vectorlst) - 1)->x * len)
        return 0;
    id = lines_findvector(l, x, 0);
    value = vector_getbetweenvalue(x, len, *lines_getvector(l, id), *lines_getvector(l, id + 1));
    //printf("value : %f id: %d\n", value, id);
    //return vector_getbetweenvalue(i, len, a->vectors[id], a->vectors[id +1]);
    return value;
}

void lines_write(void *addr)
{
    lines *l;
    double value;

    l = (lines *)addr;
    value = lines_getvalue(l);
    pluglst_write(l->pluglst, value);
    lines_setx(l);
    lines_plugpurge(addr);
}

void lines_plugpurge(void *addr)
{
    lines* l;

    l = (lines*)addr;
    pluglst_purge((t_list**)&l->pluglst);
}
