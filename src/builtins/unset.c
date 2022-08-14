/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:40:45 by galpers           #+#    #+#             */
/*   Updated: 2022/07/26 15:42:12 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

extern char **l_environ;

int				b_unset(t_cmd *cmd)
{
	unsigned int	i;

	if (get_argv_size(cmd->argv) == 1)
		print_error("unset", "Not enough arguments");
	i = 0;
	while (cmd->argv[++i])
	{
		if (validate_env(cmd->argv[i]) && !ft_strchr(cmd->argv[i], '='))
		{
			if (remove_env(cmd->argv[i]))
				print_error("INT_ERR", "Malloc error");
		}
		else
			print_error("unset", "Invalid env name");
	}

	return (0);
}
