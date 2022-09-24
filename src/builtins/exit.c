/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 23:18:58 by drobert-          #+#    #+#             */
/*   Updated: 2022/09/02 23:18:59 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

extern char	**g_environ;

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (*str == '-' || *str == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0' || ft_strlen(str + !ft_isdigit(*str)) > 19
		|| (ft_strlen(str + !ft_isdigit(*str)) >= 19 && ((*str == '+'
					&& ft_strncmp("9223372036854775807", str + 1, 20) < 0)
				|| (*str == '-'
					&& ft_strncmp("9223372036854775808", str + 1, 20) < 0)
				|| (*str != '+'
					&& ft_strncmp("9223372036854775807", str, 20) < 0))))
		return (0);
	return (1);
}

static unsigned char	get_exit_code(const char *str)
{
	unsigned long long int	num;
	int						i;

	if (str == 0)
		return (0);
	i = 0;
	if (!ft_isdigit(*str))
		i++;
	num = 0;
	while (str[i])
		num = (num * 10) + (str[i++] - '0');
	if (str[0] == '-')
		return (256 - (num & 255));
	return (num & 255);
}

int	b_exit(t_cmd *cmdv, int i)
{
	unsigned char	exit_code;

	if (cmdv[i].argv[1] != 0 && !is_numeric(cmdv[i].argv[1]))
	{
		print_error("exit", "numeric argument required");
		exit_code = 2;
	}
	else if (get_argv_size(cmdv[i].argv) > 2)
	{
		print_error("exit", "Too many arguments");
		return (1);
	}
	else if (cmdv[i].argv[1] == 0)
		exit_code = 0;
	else
		exit_code = get_exit_code(cmdv[i].argv[1]);
	printf("exit\n");
	destroy_cmdv(cmdv);
	destroy_argv(g_environ);
	exit(exit_code);
}
