/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_argvv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:53:09 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/15 16:24:56 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static void	print_argv(char **argv)
{
	int	j;

	j = -1;
	while (argv[++j])
	{
		printf(" - argv [%d]: %s\n", j, argv[j]);
	}
}

// This is a util/debug function to print argvv
void	print_cmdv(t_cmd *cmdv)
{
	int	i;

	i = -1;
	if (!cmdv)
	{
		printf("[print_cmdv] cmdv is null\n");
		return ;
	}
	if (cmdv[0].argv && !cmdv[0].argv[0])
		printf("[print_cmdv] argv is empty\n");
	while (cmdv[++i].argv)
	{
		printf("command [%d]:\n", i);
		printf(" - in_type:  %d\n", cmdv[i].in_type);
		printf(" - out_type: %d\n", cmdv[i].out_type);
		if (cmdv[i].in_type == io_file)
			printf(" - in_file: %s\n", cmdv[i].in_file);
		if (cmdv[i].out_type == io_file || cmdv[i].out_type == io_file_append)
			printf(" - out_file: %s\n", cmdv[i].out_file);
		print_argv(cmdv[i].argv);
	}
}
