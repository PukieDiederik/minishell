/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:59:04 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/15 17:30:14 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

extern char	**g_environ;

static void	exec_child(int fd[2], t_cmd *cmd, t_cmd *cmdv)
{
	char	*path;

	set_child_fds(fd, cmd);
	if (cmd->argv && cmd->argv[0])
	{
		path = get_path(cmd->argv[0]);
		if (!path)
		{
			print_error(cmd->argv[0], "Could not find command");
			exit(127);
		}
		execve(path, cmd->argv, g_environ);
		free(path);
		print_error("INT_ERR", "Something went wrong with executing\n");
		destroy_cmdv(cmdv);
		exit(126);
	}
	destroy_cmdv(cmdv);
	exit(0);
}

static void	launch_cmd(int p[2], int fd[2], t_cmd *cmdv, int *id)
{
	int	i;

	i = *id;
	*id = fork();
	if (*id < 0)
	{
		print_error("INT_ERR", "Forking error");
		*get_last_exit_p() = 125 * EXIT_MULT;
	}
	else if (*id == 0)
	{
		default_signals();
		if ((cmdv + i + 1)->in_type == io_pipe)
			close(p[0]);
		exec_child(fd, cmdv + i, cmdv);
	}
}

static int	exec_cmds(t_cmd *cmdv, int *p, int *fd, int *ids)
{
	int	i;

	i = -1;
	while (cmdv[++i].argv)
	{
		if (set_fds(cmdv, p, fd, i))
			return (1);
		if (is_builtin(cmdv[i].argv[0]))
		{
			launch_builtin(fd, cmdv, i);
			ids[i] = -1;
		}
		else
		{
			ids[i] = i;
			launch_cmd(p, fd, cmdv, ids + i);
		}
		if (fd[0] != STDIN_FILENO)
			close(fd[0]);
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
	}
	return (0);
}

void	exec(t_cmd *cmdv)
{
	int		i;
	int		p[2];
	int		fd[2];
	int		*ids;

	if (!cmdv)
		return ;
	ids = ft_calloc(get_cmd_size(cmdv), sizeof(int));
	if (!ids)
		return ;
	i = get_cmd_size(cmdv);
	handle_cmd_signals();
	if (exec_cmds(cmdv, p, fd, ids))
	{
		*get_last_exit_p() = 121 * EXIT_MULT;
		return ;
	}
	if (ids[--i] >= 0)
		waitpid(ids[i], get_last_exit_p(), 0);
	while (i-- > 0)
		if (ids[i] >= 0)
			waitpid(ids[i], 0, 0);
	free(ids);
	handle_global_signals();
}
