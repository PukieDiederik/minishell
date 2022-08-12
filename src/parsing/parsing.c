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

t_cmd *get_cmd(char *str, t_cmd *cmd_p)
{
	cmd_p->argv = get_argv(str);
	if (!cmd_p->argv)
		return (0);
	return (cmd_p);
}

char *insert_envs(char **str)
{
	int		i;
	int		is_sqoute;
	char	*str_tmp;

	i = 0;
	str_tmp = ft_strdup(*str);
	is_sqoute = 0;
	while (str_tmp[i])
	{
		if (str_tmp[i] == '\'')
			is_sqoute = !is_sqoute;
		if (str_tmp[i] == '$' && !is_sqoute)
		{
			insert_env(&str_tmp, i);
			if (!str_tmp){
				print_error("INT_ERR", "Inserting envs");
				return (0);
			}
		}
		i++;
	}
	*str = str_tmp;
	return (*str);
}

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

int configure_io(char *str, t_cmd *cmdv)
{
	int	j;
	int	i;
	char	*tmp_str;

	j = 0;
	i = 0;

	//set default io for cmdv
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
					tmp_str	= get_qouted_str(str + i);
				else
					tmp_str = get_regular_str(str + i);
				if (!tmp_str)
					return (0);
				cmdv[j].in_file = here_doc(tmp_str);
				free(tmp_str);
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
			while(str[i] == ' ')
				i++;
			if (str[i] == '\'' || str[i] == '"')
				cmdv[j].out_file = get_qouted_str(str + i);
			else
				cmdv[j].out_file = get_regular_str(str + i);
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
	return (1);
}

//returns an array of argv pointers
t_cmd 	*parse_input(char **orig_str)
{
	t_cmd	*cmdv;
	int		cmd_count;
	int		i;
	char	*str;

	i = -1;
	if (!*orig_str)
		return (0);
	cmd_count = count_commands(*orig_str);
	if (cmd_count < 0)
		return (0);
	str = *orig_str;
	insert_envs(&str);
	free(*orig_str);
	*orig_str = str;
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
	configure_io(*orig_str, cmdv);
	return (cmdv);
}
