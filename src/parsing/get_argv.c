/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:07:07 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/11 13:04:57 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static int	check_double(char *str, char **argv, unsigned int *i)
{
	char	*str_tmp;

	if (str[*i] != '"')
		return (0);
	str_tmp = get_qouted_str(str + *i);
	*argv = process_qouted_double(str_tmp);
	*i += ft_strlen(str_tmp) + 2;
	free(str_tmp);
	return (1);
}

static int	check_single(char *str, char **argv, unsigned int *i)
{
	char	*str_tmp;

	if (str[*i] != '\'')
		return (0);
	str_tmp = get_qouted_str(str + *i);
	*argv = process_qouted_single(str_tmp);
	*i += ft_strlen(str_tmp) + 2;
	free(str_tmp);
	return (1);
}

unsigned int is_special_char(char c)
{
	return (c == ' ' || c == '<' || c == '>' || c == '"' || c == '\''
			|| c == '|' || c == '\0');
}

unsigned int skip_io_redirect(char *str, unsigned int i)
{
	unsigned int	j;

	j = 1;
	if (str[i + 1] == '<' || str[i + 1] == '>')
		j++;
	while (str[i + j] == ' ')
		j++;
	while (str[i + j] && !is_special_char(str[i + j]))
		j++;
	return (j);
}

static int	check_regular(char *str, char **argv, unsigned int *i)
{
//	char	*str_tmp;

	if (str[*i] == '|')
		return (1);
	else if (str[*i] == '>' || str[(*i) + 1] == '<')
	{
		*i += skip_io_redirect(str, *i);
		return (0);
	}
	*argv = get_regular_str(str + *i);
	*i += ft_strlen(*argv);
	return (0);
}

char	**get_argv(char *str)
{
	int				argv_count;
	char			**argv;
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	argv_count = count_argv(str);
	if (argv_count < 0)
		return (0);
	argv = ft_calloc(argv_count + 1, sizeof(char *));
	if (!argv)
		return (0);
	while (str[i] && str[i] != '|')
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (check_double(str, argv + j, &i)
			|| check_single(str, argv + j, &i))
			j++;
		else
		{
			if (check_regular(str, argv + j, &i))
				break ;
			j++;
		}
	}
	return (argv);
}
