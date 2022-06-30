/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:52:30 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/30 13:51:17 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <fcntl.h>
#include "libft.h"

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

// /.hd_
static char	*get_path(char *stop_str)
{
	char	*str;
	char	*str_home;

	str_home = getenv("HOME");
	str = ft_calloc(ft_strlen(str_home) + 11, sizeof(char));
	ft_memcpy(str, str_home, ft_strlen(str_home));
	ft_memcpy(str + ft_strlen(str_home), "/.hd_", 5);
	ft_strlcpy(str + ft_strlen(str_home) + 5, stop_str, 6);
	return (str);
}

// Reads heredoc from input, puts it in a file and returns the path to the file
// It takes stop_str, the str prompt needs to match to close the heredoc
char *here_doc(char *stop_str)
{
	int		fd;
	char	*str;
	char	*path;

	path = get_path(stop_str);
	printf("path: %s\n", path);
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd < 0)
		return (0);
	str = readline("here_doc>");
	while (str && ft_strncmp(str, stop_str, max(ft_strlen(str),
			ft_strlen(stop_str))))
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
		str = readline("here_doc>");
	}
	free(str);
	return (path);
}