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

static int	check_base(char *cmd, char **ret_path)
{
	struct stat	path_stat;

	if (ft_strchr(cmd, '/') && !access(cmd, X_OK))
	{
		stat(cmd, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			print_error(cmd, "Command is a directory");
			return (0);
		}
		*ret_path = ft_strdup(cmd);
		return (1);
	}
	return (2);
}

static int	check_paths(char **paths, char *cmd, char **ret_path, char *path)
{
	int			i;
	struct stat	path_stat;

	i = -1;
	while (paths[++i])
	{
		path = create_path(paths[i], cmd);
		if (!path)
		{
			destroy_argv(paths);
			return (0);
		}
		if (!access(path, X_OK))
		{
			stat(path, &path_stat);
			if (!S_ISDIR(path_stat.st_mode))
			{
				destroy_argv(paths);
				*ret_path = path;
				return (1);
			}
		}
		free(path);
	}
	return (2);
}

char	*get_path(char *cmd)
{
	char		**paths;
	char		*ret_path;

	ret_path = 0;
	if (!check_base(cmd, &ret_path))
		return (0);
	else if (ret_path)
		return (ret_path);
	paths = ft_split(get_env("PATH"), ':');
	if (!paths)
		return (0);
	if (!check_paths(paths, cmd, &ret_path, 0))
		return (0);
	else if (ret_path)
		return (ret_path);
	destroy_argv(paths);
	print_error(cmd, "Could not find command");
	return (0);
}
