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

int *get_last_exit_p(void)
{
	static int last_exit = 0;

	return (&last_exit);
}

static char	*create_path(char *prefix, char *suffix)
{
	char *str;

	str = ft_calloc(ft_strlen(prefix) + ft_strlen(suffix) + 2, sizeof(char));
	ft_memcpy(str, prefix, ft_strlen(prefix));
	*(str + ft_strlen(prefix)) = '/';
	ft_memcpy(str + ft_strlen(prefix) + 1, suffix, ft_strlen(suffix));
	return (str);
}

static char *get_path(char *cmd)
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

static void exec_child(int in_fd, int out_fd, t_cmd *cmd, char **envp)
{
	char *path;

//	printf("outfd: %d\n", out_fd);
	if (in_fd < 0 || out_fd < 0)
		exit(1);
	if (cmd->argv && cmd->argv[0])
	{
		path = get_path(cmd->argv[0]);
		if (!path)
			exit(127);
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		execve(path, cmd->argv, envp);
		free(path);
	}
	exit(10);
}

int exec(t_cmd *cmdv, char **envp)
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
		//if input_type == pipe, use p[0] as fd_in
		if (cmdv[i].in_type == io_pipe)
			fd[0] = p[0];
		//else if input_type != pipe and the last output_type is pipe, close p[0]
		else if (i > 0 && cmdv[i - 1].out_type == io_pipe && cmdv[i].in_type != io_pipe)
			close(p[0]);
		//if output_type == pipe, create a new pipe, use p[1] as fd_out
		if (cmdv[i].out_type == io_pipe)
		{
			pipe(p);
			fd[1] = p[1];
		}
		//fork
		id = fork();
		// CHILD
		if (id == 0)
		{
			// if input_type == file, open and set fd_in
			if (cmdv[i].in_type == io_file)
				fd[0] = open(cmdv[i].in_file, O_RDONLY);
			// if output_type == file/file_append, open and set fd_out
			if (cmdv[i].out_type == io_file)
				fd[1] = open(cmdv[i].out_file, O_CREAT | O_WRONLY, 0666);
			if (cmdv[i].out_type == io_file_append)
				fd[1] = open(cmdv[i].out_file, O_CREAT | O_WRONLY | O_APPEND, 0666);
			// execute program
			exec_child(fd[0], fd[1], cmdv + i, envp);
		}
		// PARENT
		else
		{
			if (cmdv[i].in_type == io_pipe)
				close(fd[0]);
			// close p[1]
			if (cmdv[i].out_type == io_pipe)
				close(fd[1]);
			if (cmdv[i + 1].argv == 0)
				waitpid(id, get_last_exit_p(), 0);
		}
		i++;
	}
	return (0);
}