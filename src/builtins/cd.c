/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:05:05 by drobert-          #+#    #+#             */
/*   Updated: 2022/08/23 23:05:07 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>

static int	update_envs(char *old, char *new)
{
	char	*old_env;
	char	*new_env;
	int		return_s;

	return_s = 0;
	old_env = ft_calloc(ft_strlen(old) + 8, sizeof(char));
	new_env = ft_calloc(ft_strlen(new) + 5, sizeof(char));
	if (!old_env || !new_env)
	{
		free(old_env);
		free(new_env);
		return (1);
	}
	ft_memcpy(old_env, "OLDPWD=", 7);
	ft_memcpy(old_env + 7, old, ft_strlen(old));
	ft_memcpy(new_env, "PWD=", 4);
	ft_memcpy(new_env + 4, new, ft_strlen(new));
	if (add_env(old_env) || add_env(new_env))
		return_s = 1;
	free(old_env);
	free(new_env);
	return (return_s);
}

static int	change_dir(char *path)
{
	char	cwd[1024];
	char	cwd_new[1024];

	if (!getcwd(cwd, 1024))
		print_error("cd", "Problems getting cwd");
	else if (!chdir(path))
	{
		if (!getcwd(cwd_new, 1024))
			print_error("cd", "Could not update cwd");
		else
			return (update_envs(cwd, cwd_new));
	}
	print_error("cd", "Could not change dir");
	return (1);
}

static int	old_path(void)
{
	char	cwd[1024];
	char	cwd_new[1024];
	char	*old;

	old = get_env("OLDPWD");
	if (!getcwd(cwd, 1024) || !old)
		print_error("cd", "Problems getting cwd or $OLDPWD");
	else if (!chdir(old))
	{
		if (!getcwd(cwd_new, 1024))
			print_error("cd", "Could not update cwd");
		else
		{
			printf("%s\n", cwd_new);
			return (update_envs(cwd, cwd_new));
		}
	}
	print_error("cd", "Could not change dir");
	return (1);
}

/* b_cd - BUILTIN change directory
 *
 * if it does not get 1 argument, exit
 * else if the only char is '-' switch to previous directory
 * else switch to the directory given.
 */
int	b_cd(t_cmd *cmd)
{
	if (get_argv_size(cmd->argv) == 1)
		return (change_dir(get_env("HOME")));
	else if (get_argv_size(cmd->argv) > 2)
	{
		print_error("cd", "Too many arguments");
		return (1);
	}
	if (!ft_strncmp(cmd->argv[1], "-", 2))
		return (old_path());
	return (change_dir(cmd->argv[1]));
}
