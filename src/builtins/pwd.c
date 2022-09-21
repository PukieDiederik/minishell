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
#include <unistd.h>

extern char	*g_environ;

/* b_pwd - BUILTIN pwd
 *
 * Prints current directory based on getcwd
 * if there is an error with getcwd(), print error and return !0
 */
int	b_pwd(t_cmd *cmd)
{
	char	pwd[1024];

	if (get_argv_size(cmd->argv) != 1)
		print_error("pwd", "Does not take any options/arguments");
	if (getcwd(pwd, 1024))
	{
		printf("%s\n", pwd);
		return (0);
	}
	print_error("pwd", "Could not get current working dir");
	return (1);
}
