/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_argvv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:53:09 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/12 14:57:43 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// This is a util/debug function to print argvv
void	print_argvv(char ***argvv)
{
	int	i;
	int	j;

	i = -1;
	if (!argvv)
	{
		printf("[print_argvv] argvv is null\n");
		return ;
	}
	while (argvv[++i])
	{
		printf("argvv [%d]:\n", i);
		j = -1;
		while(argvv[i][++j])
		{
			printf(" - argv [%d]: %s\n", j, argvv[i][j]);
		}
	}
}