#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#define ERR -1
#define BUFF_SIZE 1024

static char	*append(char *s1, char *s2)
{
	char	*new;

	if ((new = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
	{
		ft_strcpy(ft_strcpy(new, s1) + ft_strlen(s1), s2);
		free(s1);
	}
	return (new);
}

static int	read_buf(char buf[BUFF_SIZE + 2], int fd, char **start)
{
	int	r;

	if (ft_strequ(*start, ""))
	{
		ft_bzero(buf, BUFF_SIZE + 2);
		if ((r = read(fd, buf, BUFF_SIZE)) <= 0)
			return (r == 0 ? 0 : ERR);
		*start = buf;
	}
	return (1);
}

int		gnlite(const int fd, char **line)
{
	static char		buf[BUFF_SIZE + 2] = {'\0'};
	static char		*start = buf;
	char			*next;
	int				r;

	if (!line || !(*line = ft_strdup("")))
		return (ERR);
	while (42)
	{
		if ((r = read_buf(buf, fd, &start)) <= 0)
			return (r);
		if ((next = ft_strchr(start, '\n')))
			*next = '\0';
		*line = append(*line, start);
		if (next || (next = start + ft_strlen(start)) != buf + BUFF_SIZE)
		{
			start = next + 1;
			return (1);
		}
		start = start + ft_strlen(start) + 1;
	}
}
