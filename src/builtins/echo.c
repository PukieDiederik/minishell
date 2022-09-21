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
#include <stdio.h>

/* b_echo - BUILTIN echo
 *
 * Takes in 0-n arguments
 * if first argument is "-n" do not add a newline after printing
 * else go through each arg and print it
 * if its not the last element, print a space between each arg
 */
int	b_echo(t_cmd *cmd)
{
	int		i;
	int		b;

	i = 0;
	b = 0;
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
	{
		i++;
		b = 1;
	}
	while (cmd->argv[++i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
	}
	if (b == 0)
	{
		printf("\n");
	}
	return (0);
}
