/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:27:31 by galpers           #+#    #+#             */
/*   Updated: 2022/06/24 14:30:17 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static	int		number_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	b_echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (number_args(args) > 1)
	{
		if(args[1] && ft_strncmp(args[1], "-n", 2) == 0)
		{
			write(1, args[1] + 2, ft_strlen(args[1] + 2));
			i++;
			n = 1;
		}
		while (args[i])
		{
			write(1, args[i], sizeof(args[i]));
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}