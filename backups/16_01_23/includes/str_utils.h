#ifndef STR_UTILS_H
#define STR_UTILS_H

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *str, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_itoa(int n);
int     strtabsize(char **strs);
void    strtabfree(char **strs);
int     strintab(char **strs, char *str);

#endif