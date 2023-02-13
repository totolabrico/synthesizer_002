/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:30:08 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/07 18:18:44 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	l;
	int		i;

	l = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == l)
			return ((char *)&s[i]);
		i++;
	}
	if (l == 0)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*copy;

	len = ft_strlen(s1);
	if (len == 0)
		return NULL;
	i = 0;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	*ft_strjoin(char const *s1, char const *s2) 
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	else if(!s1)
		return ft_strdup(s2);
	else if (!s2)
		return ft_strdup(s1);
	p = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		p[i + j] = (char)s2[j];
		j++;
	}
	p[i + j] = 0;
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		l = 0;
	else
	{
		l = ft_strlen(&s[start]);
		if (l > len)
			l = len;
	}
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	i = start;
	while (i < l + start && s[i])
	{
		str[i - start] = s[i];
		i++;
	}
	str[i - start] = 0;
	return (str);
}
