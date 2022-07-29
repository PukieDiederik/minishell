/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:22:13 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/25 15:22:56 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

static char	*create_path(char *prefix, char *suffix)
{
	char	*str;

	str = ft_calloc(ft_strlen(prefix) + ft_strlen(suffix) + 2, sizeof(char));
	ft_memcpy(str, prefix, ft_strlen(prefix));
	*(str + ft_strlen(prefix)) = '/';
	ft_memcpy(str + ft_strlen(prefix) + 1, suffix, ft_strlen(suffix));
	return (str);
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	while (paths[i])
	{
		path = create_path(paths[i], cmd);
		if (!access(path, X_OK))
		{
			destroy_argv(paths);
			return (path);
		}
		free(path);
		i++;
	}
	destroy_argv(paths);
	return (0);
}
