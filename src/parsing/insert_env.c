/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:58:21 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/29 12:02:06 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "minishell.h"

static char	*get_env_str(char *str)
{
	int		i;
	char	*str_tmp;

	i = 1;
	if (str[i] == '?')
		i++;
	else
		while (!is_special_char(str[i]))
			i++;
	str_tmp = ft_calloc(i, sizeof(char));
	if (!str_tmp)
		return (0);
	ft_memcpy(str_tmp, str + 1, i - 1);
	return (str_tmp);
}

static char	*no_env(char *env_str, char **str, int i)
{
	char	*str_tmp;

	str_tmp = ft_calloc((ft_strlen(*str)
				- ft_strlen(env_str)) + 1, sizeof(char));
	if (!str_tmp)
		return (0);
	ft_memcpy(str_tmp, *str, i);
	ft_memcpy(str_tmp + i,
		*str + i + ft_strlen(env_str) + 1,
		ft_strlen(*str + i + ft_strlen(env_str)) - 1);
	free(env_str);
	free(*str);
	*str = str_tmp;
	return (*str);
}

static char	*has_env(char *env_str, char **str, char *env, int i)
{
	char	*str_tmp;

	str_tmp = ft_calloc((ft_strlen(*str) - ft_strlen(env_str))
			+ ft_strlen(env) + 1, sizeof(char));
	if (!str_tmp)
		return (0);
	ft_memcpy(str_tmp, *str, i);
	ft_memcpy(str_tmp + i, env, ft_strlen(env));
	ft_memcpy(str_tmp + i + ft_strlen(env),
		*str + i + (ft_strlen(env_str) + 1),
		ft_strlen(*str + i + (ft_strlen(env_str) + 1)));
	if (env_str[0] == '?')
		free(env);
	free(*str);
	free(env_str);
	*str = str_tmp;
	return (*str);
}

char	*insert_env(char **str, int i)
{
	char	*env_str;
	char	*env;

	env_str = get_env_str(*str + i);
	if (!env_str)
		return (0);
	if (!*env_str)
	{
		free(env_str);
		return (*str);
	}
	if (env_str[0] == '?')
		env = ft_itoa(WEXITSTATUS(*get_last_exit_p()));
	else
		env = get_env(env_str);
	if (!env)
		return (no_env(env_str, str, i));
	return (has_env(env_str, str, env, i));
}

char	*insert_envs(char **str)
{
	int		i;
	int		is_sqoute;
	char	*str_tmp;

	i = 0;
	str_tmp = ft_strdup(*str);
	is_sqoute = 0;
	while (str_tmp[i])
	{
		if (str_tmp[i] == '\'')
			is_sqoute = !is_sqoute;
		if (str_tmp[i] == '$' && !is_sqoute)
		{
			insert_env(&str_tmp, i);
			if (!str_tmp)
			{
				print_error("INT_ERR", "Inserting envs");
				return (0);
			}
		}
		i++;
	}
	*str = str_tmp;
	return (*str);
}
