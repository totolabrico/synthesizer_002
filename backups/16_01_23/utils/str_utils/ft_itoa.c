#include "main.h"

static int	ft_intlen(int n)
{
	unsigned int	v;
	int				l;
	int				s;

	l = 1;
	s = 0;
	if (n < 0)
	{
		v = -n;
		s = 1;
	}
	else
		v = n;
	while (v / 10 > 0)
	{
		l++;
		v = v / 10;
	}
	return (l + s);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	v;
	int				i;
	int				neg;

	str = malloc(sizeof(char) * (ft_intlen(n) + 1));
	neg = 0;
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		neg = 1;
		v = -n;
	}
	else
		v = n;
	i = ft_intlen(n);
	while (--i >= neg)
	{
		str[i] = v % 10 + '0';
		v /= 10;
	}
	str[ft_intlen(n)] = 0;
	return (str);
}
