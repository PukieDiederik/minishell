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
#include <stdio.h>
#include <sys/stat.h>

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
	struct stat path_stat;

	i = 0;
	paths = ft_split(get_env("PATH"), ':');
	if (ft_strchr(cmd, '/') && !access(cmd, X_OK))
	{
		stat(cmd, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			print_error(cmd, "Command is a directory");
			return (0);
		}
		return (ft_strdup(cmd));
	}
	while (paths[i])
	{
		path = create_path(paths[i], cmd);
		if (!access(path, X_OK))
		{
			stat(path, &path_stat);
			if (!S_ISDIR(path_stat.st_mode))
			{
				destroy_argv(paths);
				return (path);
			}
		}
		free(path);
		i++;
	}
	destroy_argv(paths);
	print_error(cmd, "Could not find command");
	return (0);
}
