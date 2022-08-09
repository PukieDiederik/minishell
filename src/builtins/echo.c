/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:27:31 by galpers           #+#    #+#             */
/*   Updated: 2022/06/24 14:30:17 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

static char	*skip_qouted(const char *str)
{
	char	c;

	c = *str;
	str++;
	while (*str && *str != c)
		str++;
	str++;
	return ((char *)str);
}

static char	*skip_regular (const char *str)
{
	while (*str && !is_special_char(*str))
		str++;
	return ((char *)str);
}

static char	*b_skip_redirect(char *str)
{
	if (str[0] == '<' && str[1] != '<')
		str += 1;
	else if (str[0] == '<' && str[1] == '<')
		str += 2;
	else if (str[0] == '>' && str[1] != '>')
		str += 1;
	else if (str[0] == '>' && str[1] == '>')
		str += 2;
	while (*str == ' ')
		str++;
	if (*str == '\'' || *str == '"')
		str = skip_qouted(str);
	else
		str = skip_regular(str);
	return (str);
}

static char	*skip_argv(char *str)
{
	int is_done = 0;

	while (!is_done && *str) {
		is_done = 1;
		while (*str == ' ')
			str++;
		if (*str == '<' || *str == '>')
		{
			is_done = 0;
			str = b_skip_redirect(str);
		}
	}
	if (*str == '"' || *str == '\'')
		str = skip_qouted(str);
	else
		str = skip_regular(str);
	return (str);
}

int	b_echo(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	n = 0;
	str = cmd->str;
	if(cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 2) == 0)
	{
		write(1, cmd->argv[1] + 2, ft_strlen(cmd->argv[1] + 2));
		i++;
		n = 1;
	}
	while (cmd->argv[++i])
	{
		str = skip_argv(str);
		if (*str == ' ' && i > 1)
			write(1, " ", 1);
		write(1, cmd->argv[i], ft_strlen(cmd->argv[i]));
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}