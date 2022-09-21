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

/* remove_env - Remove enviroment variable from the list
 *
 * Removes an env variable based on a string
 * if the env variable does not exist, return
 * dupe env array but skip if it is the env pointer
 */
int	remove_env(char *env)
{
	char			**new_env;
	unsigned int	i;
	unsigned int	j;
	char			**skip_env;

	skip_env = get_env_p(env);
	if (!skip_env)
		return (0);
	new_env = ft_calloc(get_argv_size(g_environ), sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	j = 0;
	while (g_environ[i])
	{
		if (g_environ + i == skip_env)
			free(g_environ[i]);
		else
			new_env[j++] = g_environ[i];
		i++;
	}
	free(g_environ);
	g_environ = new_env;
	return (0);
}
