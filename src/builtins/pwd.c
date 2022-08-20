/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:49:17 by galpers           #+#    #+#             */
/*   Updated: 2022/06/24 14:56:25 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

extern char *l_environ;

int		b_pwd(t_cmd *cmd)
{
	char	*pwd;

	if (get_argv_size(cmd->argv) != 1)
		print_error("pwd", "Does not take any options/arguments");
	pwd = get_env("PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	print_error("pwd", "Could not find $PWD");
	return (1);
}
