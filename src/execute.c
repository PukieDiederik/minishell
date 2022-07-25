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
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

static void set_child_fds(int fd[2], t_cmd *cmd)
{
	if (cmd->in_type == io_file)
		fd[0] = open(cmd->in_file, O_RDONLY);
	if (cmd->out_type == io_file)
		fd[1] = open(cmd->out_file, O_CREAT | O_WRONLY, 0666);
	else if (cmd->out_type == io_file_append)
		fd[1] = open(cmd->out_file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd[0] < 0 || fd[1] < 0)
		exit(126);
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

static void	exec_child(int fd[2], t_cmd *cmd, char **envp)
{
	char	*path;

	if (cmd->argv && cmd->argv[0])
	{
		path = get_path(cmd->argv[0]);
		if (!path)
			exit(127);
		set_child_fds(fd, cmd);
		execve(path, cmd->argv, envp);
		free(path);
	}
	exit(127);
}

static void	parent(t_cmd *cmd, int fd[2], pid_t id)
{
	if (cmd->in_type == io_pipe)
		close(fd[0]);
	if (cmd->out_type == io_pipe)
		close(fd[1]);
	if ((cmd + 1)->argv == 0)
		waitpid(id, get_last_exit_p(), 0);
}

static void	set_fds(t_cmd *cmdv, int p[2], int fd[2], int i)
{
	if (cmdv[i].in_type == io_pipe)
		fd[0] = p[0];
	else if (i > 0 && cmdv[i - 1].out_type == io_pipe
		&& cmdv[i].in_type != io_pipe)
		close(p[0]);
	if (cmdv[i].out_type == io_pipe)
	{
		pipe(p);
		fd[1] = p[1];
	}
}

int	exec(t_cmd *cmdv, char **envp)
{
	int		i;
	pid_t	id;
	int		p[2];
	int		fd[2];

	if (!cmdv)
		return (0);
	i = 0;
	while (cmdv[i].argv)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = STDOUT_FILENO;
		set_fds(cmdv, p, fd, i);
		id = fork();
		if (id == 0)
			exec_child(fd, cmdv + i, envp);
		parent(cmdv + i, fd, id);
		i++;
	}
	return (0);
}
