/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:52:30 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/17 12:01:18 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include "libft.h"
#include <minishell.h>

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static char *create_path(int i)
{
	char	*str;
	char	*str_num;

	str_num = ft_itoa(i);
	if (!str_num)
		return (0);
	str = ft_calloc(9 + sizeof(str_num), sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, "/tmp/hd_", 8);
	ft_memcpy(str + 8, str_num, ft_strlen(str_num));
	free(str_num);
	return (str);
}

// /tmp/.hd_num
static char	*get_path()
{
	char	*str;
	int i;

	i = 0;
	str = create_path(i);
	while (str && !access(str, F_OK))
	{
		free(str);
		str = create_path(i++);
	}
	return (str);
}

// Reads heredoc from input, puts it in a file and returns the path to the file
// It takes stop_str, the str prompt needs to match to close the heredoc
char	*here_doc(char *stop_str)
{
	int		fd;
	char	*str;
	char	*path;

	path = get_path();
	if (!path)
		return (0);
	fd = open(path, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		return (0);
	str = readline(C_GREEN"hd"C_CYAN"> "C_RESET);
	while (str && ft_strncmp(str, stop_str,
			max(ft_strlen(str), ft_strlen(stop_str))))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline(C_GREEN"hd"C_CYAN"> "C_RESET);
	}
	close(fd);
	free(str);
	return (path);
}
