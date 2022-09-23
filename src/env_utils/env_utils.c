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

/* validate_env - validate enviroment string
 *
 * Validates enviroment string both with '=' and without
 */
int	validate_env(char *env)
{
	if (!((*env >= 'A' && *env <= 'Z') || (*env >= 'a' && *env <= 'z')
		|| *env == '_'))
		return (0);
	env++;
	while (ft_isalnum(*env) || *env == '_')
		env++;
	return (*env == '=' || *env == '\0');
}

/* get_env_p - get enviroment pointer
 *
 * Gets pointer to start of env variable based on a string
 * if there is a '=' in the string and if so only check the first part
 * else just use the string length
 * loop through each environ variable and try to find the correct string
 */
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
