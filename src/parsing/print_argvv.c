/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_argvv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:53:09 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/04 13:50:09 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

// This is a util/debug function to print argvv
void	print_cmdv(t_cmd *cmdv)
{
	int	i;
	int	j;

	i = -1;
	if (!cmdv)
	{
		printf("[print_cmdv] cmdv is null\n");
		return ;
	}
	if (!cmdv[0].argv)
		printf("[print_cmdv] cmdv is empty\n");
	while (cmdv[++i].argv)
	{
		printf("command [%d]:\n", i);
		j = -1;
		while (cmdv[i].argv[++j])
		{
			printf(" - argv [%d]: %s\n", j, cmdv[i].argv[j]);
		}
	}
}
