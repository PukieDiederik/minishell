/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:24:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/12 15:41:11 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"

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

//should process the string
char	*process_qouted_double(char *str)
{
	return (ft_strdup(str));
}

//should process the string
char	*process_qouted_single(char *str)
{
	return (ft_strdup(str));
}

//will get the argv for a single command
int	get_argv(char *str, char **argv)
{
	unsigned int	i = 0;
	int				j;
	int 			l;
	char			*str_tmp;

	//Keep looping until it finishes the string or finds |
	j = 0;
	while (str[i] && str[i] != '|')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '"')
		{
			str_tmp = get_qouted_str(str + i);
			argv[j] = process_qouted_double(str_tmp);
			i += ft_strlen(str_tmp) + 2;
			free(str_tmp);
			j++;
		}
		else if (str[i] == '\'')
		{
			str_tmp = get_qouted_str(str + i);
			argv[j] = process_qouted_single(str_tmp);
			i += ft_strlen(str_tmp) + 2;
			free(str_tmp);
			j++;
		}
		else
		{
			l = 0;
			// NOT IMPLEMENTED
			while (str[i + l] && str[i + l] != ' ' && str[i + l] != '|')
				l++;
			if (str[i + l] == '|')
				return (1);
			argv[j] = ft_calloc(l + 1, sizeof(char));
			if (!argv[j])
				return (0);
			ft_strlcpy(argv[j], str + i, l + 1);
			i += l;
			j++;
		}
	}
	return (i);
}

//returns an array of argv pointers
char ***parse_input(char *str)
{
	char	***argvv;
	int		cmd_count;
	int 	argv_count;
	int 	i;

	i = -1;
	if (!str)
		return (0);
	cmd_count = count_commands(str);
	if (cmd_count < 0)
		return (0);
	argvv = ft_calloc(cmd_count + 1, sizeof(char **));
	if (!argvv)
		return (0);
	while (++i < cmd_count)
	{
		argv_count = count_argv(str);
		argvv[i] = ft_calloc(argv_count + 1, sizeof(char *));
		if (!argvv[i] || !get_argv(str, argvv[i]))
		{
			destroy_argvv(argvv);
			return (0);
		}
		str = get_next_cmd(str);
		str++;
	}
	return (argvv);
}