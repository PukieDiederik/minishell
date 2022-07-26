/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galpers <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:54:55 by galpers           #+#    #+#             */
/*   Updated: 2022/07/26 14:26:59 by galpers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# define BUFF_SIZE 4096

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_mini
{
	t_env			*env;
	t_env			*secret_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipin;
	int				pipout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}				t_mini;

/*
** BUILTINS
*/
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_env(t_env *env);
int				ft_export(char **args, t_env *env, t_env *secret);
int				env_add(const char *value, t_env *env);
char			*get_env_name(char *dest, const char *src);
int				is_in_env(t_env *env, char *args);

/*
** FREE TOOLS
*/

void			free_env(t_env *env);
void			free_tab(char **tab);

/*
** ENV
*/
char			*env_to_str(t_env *lst);
int				env_init(t_mini *mini, char **env_array);
int				secret_env_init(t_mini *mini, char **env_array);
char			*get_env_value(char *arg, t_env *env);
char			*env_value(char *env);
int				env_value_len(const char *env);
int				is_env_char(int c);
int				is_valid_env(const char *env);
void			print_sorted_env(t_env *env);
size_t			size_env(t_env *lst);


/*
** SIGNAL
*/
void			sig_int(int code);
void			sig_quit(int code);
void			sig_init(void);

#endif