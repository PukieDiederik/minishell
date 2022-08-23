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

static int	update_env(char **env_p, char *env)
{
	free(*env_p);
	*env_p = env;
	return (0);
}

static void	add_new_env(char **new_env, char *env)
{
	int	i;

	i = -1;
	while (g_environ[++i])
		new_env[i] = g_environ[i];
	new_env[i] = env;
	free(g_environ);
	g_environ = new_env;
}

int	add_env(char *env)
{
	char	**old_env;
	char	**new_env;

	if (!validate_env(env))
		return (2);
	if (!ft_strchr(env, '='))
		return (0);
	env = ft_strdup(env);
	if (!env)
		return (1);
	old_env = get_env_p(env);
	if (old_env)
		return (update_env(old_env, env));
	new_env = ft_calloc(get_argv_size(g_environ) + 2, sizeof(char *));
	if (!new_env)
	{
		free(env);
		return (1);
	}
	add_new_env(new_env, env);
	return (0);
}
