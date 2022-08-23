/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:12:39 by galpers           #+#    #+#             */
/*   Updated: 2022/07/21 10:20:12 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"
#include <stdio.h>

extern char	**g_environ;

int	b_export(t_cmd *cmd)
{
	unsigned int	i;

	i = 0;
	if (get_argv_size(cmd->argv) == 1)
	{
		while (g_environ[i])
			printf("%s\n", g_environ[i++]);
		return (0);
	}
	while (cmd->argv[++i])
	{
		if (validate_env(cmd->argv[i]))
		{
			if (add_env(cmd->argv[i]))
			{
				print_error("INT_ERR", "Malloc error");
				return (1);
			}
		}
		else
			print_error("Export", "Invalid env");
	}
	return (0);
}
