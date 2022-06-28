/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:24:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/28 14:05:16 by drobert-         ###   ########.fr       */
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
	while (str[l] && str[l] != ' ' && str[l] != '|'
		&& str[l] != '\'' && str[l] != '"')
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

//will get the argv for a single command
//int	get_argv(char *str, char **argv)
//{
//	unsigned int	i;
//	int				j;
//	char			*str_tmp;
//
//	i = 0;
//	j = 0;
//	while (str[i] && str[i] != '|')
//	{
//		while (str[i] == ' ')
//			i++;
//		if (!str[i])
//			break ;
//		if (str[i] == '"')
//		{
//			str_tmp = get_qouted_str(str + i);
//			argv[j] = process_qouted_double(str_tmp);
//			i += ft_strlen(str_tmp) + 2;
//			free(str_tmp);
//			j++;
//		}
//		else if (str[i] == '\'')
//		{
//			str_tmp = get_qouted_str(str + i);
//			argv[j] = process_qouted_single(str_tmp);
//			i += ft_strlen(str_tmp) + 2;
//			free(str_tmp);
//			j++;
//		}
//		else
//		{
//			if (str[i] == '|')
//				break ;
//			str_tmp = get_regular_str(str + i);
//			argv[j] = process_regular(str_tmp);
//			i += ft_strlen(str_tmp);
//			free(str_tmp);
//			j++;
//		}
//	}
//	return (i);
//}

//returns an array of argv pointers
char	***parse_input(char *str)
{
	char	***argvv;
	int		cmd_count;
	int		argv_count;
	int		i;

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
