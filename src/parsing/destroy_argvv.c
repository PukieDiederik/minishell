/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_argvv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:00:41 by drobert-          #+#    #+#             */
/*   Updated: 2022/06/12 15:04:57 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// Destroys an argv array
void	destroy_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
		free(argv[i++]);
}

// Destroys an argvv array
void destroy_argvv(char ***argvv)
{
	int i;

	i = 0;
	if (!argvv)
		return ;
	while (argvv[i])
		destroy_argv(argvv[i++]);
	free(argvv);
}