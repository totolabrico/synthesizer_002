#include "main.h"

void	lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return;
	last = *lst;
	if (!last)
		*lst = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
}
void	lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = lst[0];
	lst[0] = new;
}

void	lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	last = *lst;
	while (last)
	{
		next = last->next;
		lstdelone(last, del);
		last = next;
	}
	*lst = NULL;
}

void	lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}

void	lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*l;

	if (!lst || !f)
		return ;
	l = lst;
	while (l)
	{
		f((void *)l->content);
		l = l->next;
	}
}

t_list	*lstlast(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (last && last->next)
	{
		last = last->next;
	}
	return (last);
}

t_list	*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*new;
	t_list	*map;

	if (!lst || !f || !del)
		return (NULL);
	l = lst;
	map = NULL;
	while (l)
	{
		new = lstnew(f(l->content));
		lstadd_back(&map, new);
		if (!new)
		{
			lstclear(&map, del);
			return (NULL);
		}
		l = l->next;
	}
	return (map);
}

t_list	*lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

int	lstsize(t_list *lst)
{
	int		i;
	t_list	*l;

	l = lst;
	i = 0;
	while (l)
	{
		l = l->next;
		i++;
	}
	return (i);
}

t_list	*lstget_byid(t_list *list, int id)
{
	int i;

	i = 0;
	while(list && i <= id)
	{
			if(i == id)
				return list;
			list = list->next;
			i++;
	}
	return NULL;
}

t_list	*lstget_byaddr(t_list *list, void *addr)
{
	while(list)
	{
		if(list->content == addr)
			return list;
		list = list->next;
	}
	return NULL;
}

int lstgetid_byaddr(t_list *lst, void *addr)
{
	int i;

	i = 0;
	while(lst)
	{
		if(addr == lst->content)
			return i;
		lst = lst->next;
		i++;
	}
	return -1;
}

t_list *lstpop(t_list *list, void (*del)(void*), int id)
{
	t_list *l;
	t_list *first;
	t_list *last;

	l = lstget_byid(list, id);
	first = list;
	last = NULL;
	if (!l)
		return first;
	if (id > 0)
		last = lstget_byid(list, id -1);
	if(l != lstlast(list))
	{
		if (last)
			last->next = l->next;
		else
			first = l->next;
	}
	else if (!last)
		first = NULL;
	else
		last->next = NULL;
	lstdelone(l, del);
	return first;
}

void lstpurgenull(t_list **lst, void (*del)(void*))
{
	t_list *l;
	int i;

	i = 0;
	l = *lst;
	while (l)
	{
		if (!l->content)
		{
			lstpop(*lst, del, i);
			l = lstget_byid(*lst, i);
		}
		else
		{
			l = l->next;
			i++;
		}
	}
}
