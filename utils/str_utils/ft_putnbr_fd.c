#include "main.h"

static void	ft_putabsnbr_fd(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putabsnbr_fd(n / 10, fd);
	}
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putabsnbr_fd(-n, fd);
	}
	else
	{
		ft_putabsnbr_fd(n, fd);
	}
}
