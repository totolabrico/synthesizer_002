#ifndef LIST_UTILS_H
#define LIST_UTILS_H

typedef struct s_list
{
	void	    		*content;
	struct s_list	*next;
}	t_list;

void				lstadd_back(t_list **lst, t_list *new);
void				lstadd_front(t_list **lst, t_list *new);
void				lstclear(t_list **lst, void (*del)(void*));
void				lstdelone(t_list *lst, void (*del)(void*));
void				lstiter(t_list *lst, void (*f)(void *));
t_list				*lstlast(t_list *lst);
t_list				*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list				*lstnew(void *content);
int					lstsize(t_list *lst);
t_list				*lstget_byid(t_list *list, int id);
t_list				*lstget_byaddr(t_list *list, void *addr);
t_list				 *lstpop(t_list *list, void (*del)(void*), int id);

#endif