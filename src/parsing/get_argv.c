/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:07:07 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/25 13:56:02 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static int	check_double(char *str, char **argv, unsigned int *i)
{
	if (str[*i] != '"')
		return (0);
	*argv = get_qouted_str(str + *i);
	*i += ft_strlen(*argv) + 2;
	return (1);
}

static int	check_single(char *str, char **argv, unsigned int *i)
{
	if (str[*i] != '\'')
		return (0);
	*argv = get_qouted_str(str + *i);
	*i += ft_strlen(*argv) + 2;
	return (1);
}

static int	check_regular(char *str, char **argv, unsigned int *i)
{
	if (str[*i] == '|')
		return (1);
	*argv = get_regular_str(str + *i);
	*i += ft_strlen(*argv);
	return (0);
}

static int	do_checks(char *str, char **argv, unsigned int *i, int *j)
{
	while (str[*i] == ' ')
		(*i)++;
	if (!str[*i])
		return (1);
	if (check_double(str, argv + *j, i)
		|| check_single(str, argv + *j, i))
		(*j)++;
	else if (str[*i] == '>' || str[*i] == '<')
		skip_redirect(str, (int *)i);
	else
	{
		if (check_regular(str, argv + *j, i))
			return (1);
		(*j)++;
	}
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
	{
		print_error("INT_ERR", "Malloc error");
		return (0);
	}
	while (str[i] && str[i] != '|')
	{
		if (do_checks(str, argv, &i, &j))
			break ;
	}
	return (argv);
}
