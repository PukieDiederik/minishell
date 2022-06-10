/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:24:54 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/10 15:05:33 by drobert-         ###   ########.fr       */
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

//should process the string and free `str`
int	process_qouted_double(char *str)
{
	printf("Double qouted: \"%s\"\n", str);
	return (0);
}

//should process the string
int	process_qouted_single(char *str)
{
	printf("Single qouted: \"%s\"\n", str);
	return (0);
}

//will get the argv for a single command
int	get_argv(char *str)
{
	unsigned int i = 0;
	char *str_tmp;

	//Keep looping until it finishes the string or
	printf("=== === ===\n");
	while (str[i] && str[i] != '|')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '"')
		{
			str_tmp = get_qouted_str(str + i);
			process_qouted_double(str_tmp);
			i += ft_strlen(str_tmp) + 2;
			free(str_tmp);
		}
		else if (str[i] == '\'')
		{
			str_tmp = get_qouted_str(str + i);
			process_qouted_single(str_tmp);
			i += ft_strlen(str_tmp) + 2;
			free(str_tmp);
		}
		else
		{
			// NOT IMPLEMENTED
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (i);
}

//returns an array of argv pointers
char ***parse_input(char *str)
{
	char	***argvv;
	int		cmd_count;

	if (!str)
		return (0);
	printf("===\n'%s'\n", str);
	argvv = malloc(sizeof(char ***) * 256);
	if (!argvv)
		return (0);
	cmd_count = count_commands(str);
	printf("CMD_COUNT: %d\n", cmd_count);
	return (argvv);
}