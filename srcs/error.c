/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeyer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 10:15:57 by lmeyer            #+#    #+#             */
/*   Updated: 2018/08/25 10:15:58 by lmeyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	exit_message(int exit_code, char *message)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}
