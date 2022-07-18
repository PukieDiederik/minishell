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

#include "../../include/minishell.h"

int		ft_pwd(void)
{
	char	cwd[BUFF_SIZE];

	if (getcwd(cwd, BUFF_SIZE))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}
