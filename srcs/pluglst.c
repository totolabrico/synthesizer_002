#include "main.h"

void pluglst_unplug(t_list *lst, int id)
{
    plug *p;

    lst = lstget_byid(lst, id);
    if (lst)
    {
        p = (plug*)lst->content;
        plug_setplugged(p, 0);
    }
}

void pluglst_purge(t_list **lst)
{
    t_list *l;
    int i;

    l = *lst;
    i = 0;
    while (l)
    {   
        if(plug_getplugged((plug*)l->content) == 0)
        {
            *lst = lstpop(*lst, &plug_clear, i);
            l = *lst;
            i = 0;
        }
        else
        {
            l = l->next;
            i++;
        }
    }
}

void pluglst_write(t_list *lst, double value)
{
    plug *p;

    while (lst)
    {
        p = (plug*)lst->content;
        p->method(p->dest, value);
        lst = lst->next;
    }
}

void pluglst_print(void *addr, t_list *lst, int id)
{
    plug *p;
    int i;

    if (lstsize(lst) == 0)
        return;
    printf("\t[chn:%d]", id);
    i = 0;
    while(lst)
    {
        p = (plug*)lst->content;
        plug_print(addr, p, i);
        lst = lst->next;
        i++;
    }  
    printf("\n");
}