#include "main.h"

static int	ft_strslen(char const *str, char c)
{
	int	i;
	int	len;
	int	ces;

	i = 0;
	len = 0;
	ces = 1;
	while (str[i])
	{
		if ((char)str[i] != c)
		{
			if (ces == 1)
				len++;
			ces = 0;
		}
		else
			ces = 1;
		i++;
	}
	return (len);
}

static int	ft_strclen(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

static int	ft_freesplit(char **split, char *last, int len)
{
	int	i;

	if (last)
		return (1);
	i = 0;
	while (len >= 0 && i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		pos;
	char	**split;

	if (!str)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_strslen(str, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < ft_strslen(str, c))
	{
		while (str[pos] == c)
			pos++;
		split[i] = malloc(sizeof(char) * (ft_strclen(&str[pos], c) + 1));
		if (ft_freesplit(split, split[i], i) == 0)
			return (NULL);
		ft_strlcpy(split[i], &str[pos], ft_strclen(&str[pos], c) + 1);
		pos += ft_strclen(&str[pos], c);
		i++;
	}
	split[i] = NULL;
	return (split);
}
