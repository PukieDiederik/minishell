/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:35:47 by galpers           #+#    #+#             */
/*   Updated: 2022/07/26 15:37:31 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

extern char **l_environ;

static int change_dir(char *path)
{
	char cwd[1024];
	char	*old_env;
	char	*new_env;

	if(!getcwd(cwd, 1024))
		print_error("cd", "Problems getting cwd");
	else if (!chdir(path)){
		old_env = ft_calloc(ft_strlen(cwd) + 8, sizeof(char));
		new_env = ft_calloc(ft_strlen(path) + 5, sizeof(char));
		ft_memcpy(old_env, "OLDPWD=", 7);
		ft_memcpy(old_env + 7, cwd, ft_strlen(cwd));
		ft_memcpy(new_env, "PWD=", 4);
		ft_memcpy(new_env + 4, path, ft_strlen(cwd));
		add_env(old_env);
		add_env(new_env);
		free(old_env);
		free(new_env);
		return (0);
	}
	print_error("cd", "Could not change dir");
	return (1);
}

static int old_path(void)
{
	char cwd[1024];
	char	*old;
	char	*old_env;
	char	*new_env;

	old = get_env("OLDPWD");
	if(!getcwd(cwd, 1024) || !old)
		print_error("cd", "Problems getting cwd or $OLDPWD");
	else if (!chdir(old)){
		old_env = ft_calloc(ft_strlen(cwd) + 8, sizeof(char));
		new_env = ft_calloc(ft_strlen(old) + 5, sizeof(char));
		ft_memcpy(old_env, "OLDPWD=", 7);
		ft_memcpy(old_env + 7, cwd, ft_strlen(cwd));
		ft_memcpy(new_env, "PWD=", 4);
		ft_memcpy(new_env + 4, old, ft_strlen(cwd));
		add_env(old_env);
		add_env(new_env);
		free(old_env);
		free(new_env);
		return (0);
	}
	print_error("cd", "Could not change dir");
	return (1);
}

int	b_cd(t_cmd *cmd)
{
	if (get_argv_size(cmd->argv) != 2)
	{
		print_error("cd", "Not correct amount of args");
		return (1);
	}
	if (!ft_strncmp(cmd->argv[1], "-", 2))
		return (old_path());
	else
		return (change_dir(cmd->argv[1]));
}