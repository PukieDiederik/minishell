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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

extern char **g_environ;

void set_child_fds(int fd[2], t_cmd *cmd)
{
	if (cmd->in_type == io_file)
		fd[0] = open(cmd->in_file, O_RDONLY);
	if (cmd->out_type == io_file)
		fd[1] = open(cmd->out_file, O_CREAT | O_WRONLY, 0666);
	else if (cmd->out_type == io_file_append)
		fd[1] = open(cmd->out_file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd[0] < 0 || fd[1] < 0)
		print_error_exit("INT_ERR", "Could not open file(s)", 126);
	if (fd[0] != STDIN_FILENO)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static void	exec_child(int fd[2], t_cmd *cmd, t_cmd *cmdv)
{
	char	*path;

	set_child_fds(fd, cmd);
	if (cmd->argv && cmd->argv[0])
	{
		path = get_path(cmd->argv[0]);
		if (!path)
			exit(126);
		execve(path, cmd->argv, g_environ);
		free(path);
		print_error("INT_ERR", "Something went wrong with executing\n");
		destroy_cmdv(cmdv);
		exit(127);
	}
	destroy_cmdv(cmdv);
	exit(0);
}

static void	set_fds(t_cmd *cmdv, int p[2], int fd[2], int i)
{
	if (cmdv[i].in_type == io_pipe)
		fd[0] = p[0];
	pipe(p);
	if (cmdv[i].out_type != io_pipe)
		close(p[1]);
	else
		fd[1] = p[1];
	if (cmdv[i + 1].in_type != io_pipe)
		close(p[0]);
}

static int get_cmd_size(t_cmd *cmdv)
{
	int i;

	i = 0;
	if (!cmdv)
		return (0);
	while (cmdv[i].argv)
		i++;
	return (i);
}

int	exec(t_cmd *cmdv)
{
	int		i;
	pid_t	id;
	int		p[2];
	int		fd[2];
	int		*ids;

	if (!cmdv)
		return (0);
	ids = ft_calloc(get_cmd_size(cmdv), sizeof(int));
	i = 0;
	while (cmdv[i].argv)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = STDOUT_FILENO;
		set_fds(cmdv, p, fd, i);
		if (is_builtin(cmdv[i].argv[0])) {
			launch_builtin(fd, cmdv, i);
			ids[i] = -1;
		}
		else
		{
			handle_cmd_signals();
			id = fork();
			if (id == 0)
			{
				if (cmdv[i + 1].in_type == io_pipe)
					close(p[0]);
				exec_child(fd, cmdv + i, cmdv);
			}
			ids[i] = id;
			handle_global_signals();
		}
		if (fd[0] != STDIN_FILENO)
			close(fd[0]);
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
		i++;
	}
	if (ids[--i] >= 0)
		waitpid(ids[i], get_last_exit_p(), 0);
	while (i-- > 0)
		if (ids[i] >= 0)
			waitpid(ids[i], 0, 0);
	free(ids);
	return (0);
}
