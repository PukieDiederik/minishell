/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:25:06 by drobert-          #+#    #+#             */
/*   Updated: 2022/08/23 23:25:07 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern char	**g_environ;

int	validate_env(char *env)
{
	while ((*env >= 'A' && *env <= 'Z') || (*env >= 'a' && *env <= 'z')
		|| *env == '_')
		env++;
	return (*env == '=' || *env == '\0');
}

char	**get_env_p(char *env)
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
			return (g_environ + i);
	return (0);
}
