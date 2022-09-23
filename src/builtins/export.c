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
#include "libft.h"

extern char	**g_environ;

static char *get_env_name(char *env)
{
	char *eq_p;
	char *ret;

	eq_p = ft_strchr(env, '=');
	if (!eq_p)
		return (ft_strdup(env));
	ret = ft_calloc(eq_p - env + 1, sizeof(char));
	ft_memcpy(ret, env, eq_p - env);
	return ret;
}

static int print_env()
{
	char **sorted;
	char *name;
	int i;

	sorted = ft_calloc(get_argv_size(g_environ) + 1, sizeof(char *));
	if (!sorted)
	{
		print_error("INT_ERR", "Malloc Error");
		return (1);
	}
	ft_memcpy(sorted, g_environ, get_argv_size(g_environ) * sizeof(char *));
	quick_sort(sorted, 0, get_argv_size(sorted) - 1);
	i = 0;
	while (sorted[i])
	{
		name = get_env_name(sorted[i]);
		if (!name)
		{
			print_error("INT_ERR", "Malloc error");
			return (1);
		}
		if (ft_strchr(sorted[i], '='))
			printf("declare -x %s=\"%s\"\n", name, ft_strchr(sorted[i], '=') + 1);
		else
			printf("declare -x %s\n", name);
		free(name);
		i++;
	}
	free(sorted);
	return (0);
}
/* b_export - BUILTIN export
 *
 * Adds enviroment variables
 * if it does not have any arguments, print every env variable
 * else go through each argument and try to add it
 */
int	b_export(t_cmd *cmd)
{
	unsigned int	i;

	i = 0;
	if (get_argv_size(cmd->argv) == 1)
		return (print_env());
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
