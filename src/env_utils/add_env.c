/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:22:31 by drobert-          #+#    #+#             */
/*   Updated: 2022/08/23 23:22:32 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

extern char	**g_environ;

char	**get_env_p(char *env);

int	add_env(char *env)
{
	char	**old_env;
	char	**new_env;
	int		i;

	if (!ft_strchr(env, '='))
		return (0);
	if (!validate_env(env))
		return (2);
	new_env = ft_calloc(get_argv_size(g_environ) + 2, sizeof(char *));
	env = ft_strdup(env);
	if (!env || !new_env || !validate_env(env))
	{
		free(new_env);
		free(env);
		return (1);
	}
	old_env = get_env_p(env);
	if (old_env)
	{
		free(*old_env);
		*old_env = env;
		free(new_env);
		return (0);
	}
	i = 0;
	while (g_environ[i])
	{
		new_env[i] = g_environ[i];
		i++;
	}
	new_env[i] = env;
	free(g_environ);
	g_environ = new_env;
	return (0);
}
