/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:24:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/13 13:23:01 by drobert-         ###   ########.fr       */
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
	sub_str = malloc(sizeof(char) * s);
	if (!sub_str)
		return (0);
	*(sub_str + s - 1) = 0;
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
		return (0);
	ft_memcpy(sub_str, str, l);
	return (sub_str);
}

//should process the string
char	*process_qouted_double(char *str)
{
	int		i;
	char	*str_tmp;
	char	*str_tmp2;

	i = 0;
	str_tmp2 = ft_strdup(str);
	while (str_tmp2[i])
	{
		while (str_tmp2[i] && str_tmp2[i] != '$')
			i++;
		if (!str_tmp2[i])
			break ;
		str_tmp = insert_env(str_tmp2, i);
		free(str_tmp2);
		if (!str_tmp)
			return (0);
		str_tmp2 = str_tmp;
		i++;
	}
	return (str_tmp2);
}

//should process the string
char	*process_qouted_single(char *str)
{
	return (ft_strdup(str));
}

char	*process_regular(char *str)
{
	int		i;
	char	*str_tmp;
	char	*str_tmp2;

	i = 0;
	str_tmp2 = ft_strdup(str);
	while (str_tmp2[i])
	{
		while (str_tmp2[i] && str_tmp2[i] != '$')
			i++;
		if (!str_tmp2[i])
			break ;
		str_tmp = insert_env(str_tmp2, i);
		free(str_tmp2);
		if (!str_tmp)
			return (0);
		str_tmp2 = str_tmp;
		i++;
	}
	return (str_tmp2);
}

t_cmd *get_cmd(char *str, t_cmd *cmd_p)
{
	cmd_p->argv = get_argv(str);
	if (!cmd_p->argv)
		return (0);
	cmd_p->in_type = io_none;
	cmd_p->out_type = io_none;
	return (cmd_p);
}

char *insert_envs(char *str)
{
	int		i;
	int		is_sqoute;
	char	*str_tmp;

	i = 0;
	str_tmp = ft_strdup(str);
	is_sqoute = 0;
	while (str_tmp[i])
	{
		if (str_tmp[i] == '\'')
			is_sqoute = !is_sqoute;
		printf("%c %d\n", str_tmp[i], is_sqoute);
		if (str_tmp[i] == '$' && !is_sqoute)
		{
			str = insert_env(str_tmp, i);
			free(str_tmp);
			str_tmp = str;
			if(str[i] != '$')
				i--;
			printf("%s\n", str_tmp);
		}
		i++;
	}
	return (str_tmp);
}

//returns an array of argv pointers
t_cmd 	*parse_input(char *str)
{
	t_cmd	*cmdv;
	int		cmd_count;
	int		i;
	char	*org_str;

	i = -1;
	if (!str)
		return (0);
	cmd_count = count_commands(str);
	str = insert_envs(str);
	org_str = str;
	if (cmd_count < 0)
		return (0);
	cmdv = ft_calloc(cmd_count + 1, sizeof(t_cmd));
	if (!cmdv)
		return (0);
	while (++i < cmd_count)
	{
		if (!get_cmd(str, cmdv + i))
			return (0);
		str = get_next_cmd(str);
		str++;
	}
	free(org_str);
	return (cmdv);
}
