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
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	b_echo(t_cmd *cmd)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if(cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
	{
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
		n = 1;
	}
	while (cmd->argv[++i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
	}
	if (n == 0)
		printf("\n");
	return (0);
}