/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:22:45 by drobert-          #+#    #+#             */
/*   Updated: 2022/08/23 23:22:49 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern char	**g_environ;

/* get_env - Get enviroment variable
 *
 * Gets the enviroment variable based on a string
 * if it has '=' in string only use the first part for comparison
 * loop through each env var and check if the first part is the same
 */
char	*get_env(char *env)
{
	unsigned int	i;
	unsigned int	s_env;

	i = -1;
	if (ft_strchr(env, '='))
		s_env = ft_strchr(env, '=') - env;
	else
		s_env = ft_strlen(env);
	while (g_environ[++i])
		if (!ft_strncmp(g_environ[i], env, s_env) && g_environ[i][s_env] == '=')
			return (ft_strchr(g_environ[i], '=') + 1);
	return (0);
}
