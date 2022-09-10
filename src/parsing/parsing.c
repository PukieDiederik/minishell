/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:24:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/17 12:33:45 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

//assumes the first character is either a double or single qoute
char	*get_qouted_str(char *str)
{
	int		s;
	char	*sub_str;

	if (!str || (*str != '\'' && *str != '"'))
		return (0);
	s = (int)(ft_strchr(str + 1, *str) - str);
	sub_str = ft_calloc(s, sizeof(char));
	if (!sub_str)
	{
		print_error("INT_ERR", "Malloc error");
		return (0);
	}
	ft_memcpy(sub_str, str + 1, s - 1);
	return (sub_str);
}

char	*get_regular_str(char *str)
{
	int		l;
	char	*sub_str;

	l = 0;
	while (!is_special_char(*(str + l)))
		l++;
	sub_str = ft_calloc(l + 1, sizeof(char));
	if (!sub_str)
	{
		print_error("INT_ERR", "Malloc error");
		return (0);
	}
	ft_memcpy(sub_str, str, l);
	return (sub_str);
}

t_cmd	*get_cmd(char *str, t_cmd *cmd_p)
{
	cmd_p->argv = get_argv(str);
	if (!cmd_p->argv)
		return (0);
	return (cmd_p);
}

static int	setup(int *cmd_count, char **orig_str, char **str)
{
	if (!*orig_str)
		return (1);
	*cmd_count = count_commands(*orig_str);
	if (*cmd_count < 0)
		return (1);
	*str = *orig_str;
	insert_envs(str);
	free(*orig_str);
	*orig_str = *str;
	return (0);
}

//returns an array of argv pointers
t_cmd	*parse_input(char **orig_str)
{
	t_cmd	*cmdv;
	int		cmd_count;
	int		i;
	char	*str;

	if (setup(&cmd_count, orig_str, &str))
		return (0);
	i = -1;
	cmdv = ft_calloc(cmd_count + 1, sizeof(t_cmd));
	if (!cmdv || !str)
		return (0);
	while (++i < cmd_count)
	{
		if (!get_cmd(str, cmdv + i))
			return (0);
		str = get_next_cmd(str);
		str++;
	}
	if (configure_io(*orig_str, cmdv))
	{
		destroy_cmdv(cmdv);
		return (0);
	}
	return (cmdv);
}
