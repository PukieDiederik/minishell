/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 00:49:15 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/10 00:49:17 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	skip_regular(const char *str, int *i, int *c)
{
	while (str[*i] && !is_special_char(str[*i]))
		(*i)++;
	if (str[*i] == '|')
	{
		(*c)++;
		(*i)++;
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			(*i)++;
	}
	return (0);
}

static int	skip_qouted(const char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (!str[*i])
		return (1);
	(*i)++;
	return (0);
}

int	configure_io(char *str, t_cmd *cmdv)
{
	int		j;
	int		i;
	char	*tmp_str;

	j = 0;
	i = 0;
	while (cmdv[j].argv)
	{
		cmdv[j].in_type = io_none;
		cmdv[j].in_file = 0;
		cmdv[j].out_type = io_none;
		cmdv[j].out_file = 0;
		j++;
	}
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '<')
		{
			cmdv[j].in_type = io_file;
			if (cmdv[j].in_file != 0)
				free(cmdv[j].in_file);
			i++;
			if (str[i] == '<')
			{
				i++;
				while (str[i] == ' ')
					i++;
				if (str[i] == '\'' || str[i] == '"')
					tmp_str = get_qouted_str(str + i);
				else
					tmp_str = get_regular_str(str + i);
				if (!tmp_str)
					return (1);
				cmdv[j].in_file = launch_hd(tmp_str);
				free(tmp_str);
				if (!cmdv[j].in_file)
					return (1);
			}
			else
			{
				while (str[i] == ' ')
					i++;
				if (str[i] == '\'' || str[i] == '"')
					cmdv[j].in_file = get_qouted_str(str + i);
				else
					cmdv[j].in_file = get_regular_str(str + i);
			}
		}
		if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
			{
				cmdv[j].out_type = io_file_append;
				i++;
			}
			else
				cmdv[j].out_type = io_file;
			while (str[i] == ' ')
				i++;
			if (str[i] == '\'' || str[i] == '"')
				cmdv[j].out_file = get_qouted_str(str + i);
			else
				cmdv[j].out_file = get_regular_str(str + i);
			if (!cmdv[j].out_file)
				return (1);
		}
		if (str[i] == '|')
		{
			if (cmdv[j].out_type == io_none)
				cmdv[j].out_type = io_pipe;
			cmdv[j + 1].in_type = io_pipe;
			j++;
			i++;
		}
		if (str[i] == '\'' || str[i] == '"')
			skip_qouted(str, &i);
		else
			skip_regular(str, &i, &j);
	}
	return (0);
}
