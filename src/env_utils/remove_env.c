/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:22:22 by drobert-          #+#    #+#             */
/*   Updated: 2022/08/23 23:22:23 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

extern char	**g_environ;

char	**get_env_p(char *env);

int	remove_env(char *env)
{
	char			**new_env;
	unsigned int	i;
	unsigned int	j;
	unsigned int	env_s;

	if (!get_env_p(env))
		return (0);
	new_env = ft_calloc(get_argv_size(g_environ), sizeof(char *));
	if (!new_env)
		return (1);
	env_s = ft_strlen(env);
	i = 0;
	j = 0;
	while (g_environ[i])
	{
		if (!ft_strncmp(g_environ[i], env, env_s) && g_environ[i][env_s] == '=')
			free(g_environ[i]);
		else
			new_env[j++] = g_environ[i];
		i++;
	}
	free(g_environ);
	g_environ = new_env;
	return (0);
}
