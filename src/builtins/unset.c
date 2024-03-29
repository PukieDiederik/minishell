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

extern char	**g_environ;

/* b_unset - BUILTIN unset
 *
 * Removes env variable
 * if it does not have any args, print error
 * run through each arg, try to remove each env
 */
int	b_unset(t_cmd *cmd)
{
	unsigned int	i;

	if (get_argv_size(cmd->argv) == 1)
	{
		print_error("unset", "Not enough arguments");
		return (1);
	}
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
