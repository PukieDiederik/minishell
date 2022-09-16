/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 03:09:00 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/08 03:09:02 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

void	set_child_fds(int fd[2], t_cmd *cmd)
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

void	set_fds(t_cmd *cmdv, int p[2], int fd[2], int i)
{
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	if (cmdv[i].in_type == io_pipe)
		fd[0] = p[0];
	else if (i > 0)
		close(p[0]);
	pipe(p);
	if (cmdv[i].out_type != io_pipe)
		close(p[1]);
	else
		fd[1] = p[1];
	if (!cmdv[i + 1].argv)
		close(p[0]);
}
