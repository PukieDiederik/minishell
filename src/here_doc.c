/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:52:30 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/11 09:54:13 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include "libft.h"
#include <unistd.h>

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}


// /tmp/msh_hd_[num]
static char	*get_path(unsigned int i)
{
	char	*str;
	char	*str_num;

	str_num = ft_itoa(i);
	str = ft_calloc(ft_strlen(str_num) + 13, sizeof(char));
	if (!str || !str_num) {
		free(str_num);
		free(str);
		return (0);
	}
	ft_memcpy(str, "/tmp/msh_hd_", 12);
	ft_memcpy(str + 12, str_num, ft_strlen(str_num));
	free(str_num);
	return (str);
}

static char *get_unique_path()
{
	char				*path;
	unsigned int		i;

	i = 0;
	path = get_path(i);
	if (!path)
		return (0);
	while (!access(path, F_OK))
	{
		free(path);
		path = get_path(++i);
		if (!path)
			return (0);
	}
	return (path);
}

// Reads heredoc from input, puts it in a file and returns the path to the file
// It takes stop_str, the str prompt needs to match to close the heredoc
char	*here_doc(char *stop_str)
{
	int		fd;
	char	*str;
	char	*path;

	path = get_unique_path();
	if (!path)
		return (0);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
	{
		free(path);
		return (0);
	}
	str = readline("here_doc>");
	while (str && ft_strncmp(str, stop_str,
			max(ft_strlen(str), ft_strlen(stop_str))))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("here_doc>");
	}
	close(fd);
	free(str);
	return (path);
}
