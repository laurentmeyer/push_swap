#include "push_swap.h"
#include "libft.h"

int	exit_message(int exit_code, char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}