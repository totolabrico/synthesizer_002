#include "get_next_line.h"

#define BUFFER_SIZE 1

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*s;
	char		*d;

	if ((!dst && !src))
		return (dst);
	d = (char *)dst;
	s = src;
	i = 0;
	while (i < len)
	{
		if (dst <= src)
			d[i] = s[i];
		else
			d[len - i - 1] = s[len - i - 1];
		i++;
	}
	return (dst);
}

static void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*str;

	str = (char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

static char *ft_strfreejoin(char *str, char *add)
{
  char *res;

  res = ft_strjoin(str, add);
  if(str)
    free(str);
  return res;
}

char *get_next_line(int fd)
{
  int len;
  static char buf[BUFFER_SIZE];
  char copy[BUFFER_SIZE + 1];
  char *res;
  void *pos;
  void *add;

  res = NULL;
  pos = NULL;
  len = BUFFER_SIZE;
  while (!pos && len != 0)
  {
    ft_strlcpy(copy, buf, len + 1);
    pos = ft_strchr(buf, '\n');
    if (pos)
      len = (long)pos + 1 - (long)buf;
    add = ft_substr(copy, 0, len );
    res = ft_strfreejoin(res, add);
    free(add);
    if (!pos)
      len = read(fd, buf, BUFFER_SIZE);
  }
  if (len != 0)
  { 
    ft_memmove(buf, buf + len, BUFFER_SIZE - len);
    ft_memset(&buf[BUFFER_SIZE - len], 0, len);
  }
  else
    ft_memset(buf, 0, BUFFER_SIZE);
  /*
  printf(">>>%s<<<\n", res);
  printf("[");
  for (int i = 0; i < BUFFER_SIZE; i++)
  {
    if (buf[i] == 0)
        printf("X");
    else
      printf("%c", buf[i]);
  }
  printf("]\n");
  */
  return res;
}

