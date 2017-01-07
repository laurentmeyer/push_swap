#include "ft_printf.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		main(void)
{
	int		fd;
	char	*s;

	//fd = open("tags", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	while ((gnlite(fd, &s)))
	{
		ft_printf("{%s}\n", s);
		free(s);
	}
	close(fd);
	return (0);
}
