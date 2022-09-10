/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drobert- <drobert-@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:35:51 by drobert-          #+#    #+#             */
/*   Updated: 2022/07/17 12:09:50 by drobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

// Definitions
// Colors
# define C_BLACK "\033[0;30m"
# define C_RED "\033[0;31m"
# define C_GREEN "\033[0;32m"
# define C_ORANGE "\033[0;33m"
# define C_BLUE	 "\033[0;34m"
# define C_PURPLE "\033[0;35m"
# define C_CYAN "\033[0;36m"
# define C_GRAY "\033[0;37m"
# define C_WHITE "\033[0;38m"
# define C_RESET "\033[0m"

# define EXIT_MULT 256

// Structures
/* e_io_type - What kind of io a command uses
 *
 * none			- Uses regular io file descriptors
 * pipe			- Remaps regular io file descriptors to a pipe
 * file			- Opens a file and remaps io file descriptors to file descriptor
 * file_append	- Same as file but opens it in append mode
 */
typedef enum e_io_type
{
	io_none,
	io_pipe,
	io_file,
	io_file_append
}	t_iotype;

/* s_cmd - structure which holds information for each command
 *
 * argv			- Holds the argument vector for a command
 * in/out_type	- Hold the type of input/output
 * in/out_file	- Holds a path to the input/output file if in/out_type is file
 */
typedef struct s_cmd
{
	char		**argv;
	t_iotype	in_type;
	t_iotype	out_type;
	char		*in_file;
	char		*out_file;
}	t_cmd;

// Functions
// Parsing
t_cmd			*parse_input(char **orig_str);
int				count_commands(const char *str);
int				count_argv(const char *str);
char			*get_next_cmd(const char *str);
char			*insert_env(char **str, int i);
char			*insert_envs(char **str);
char			**get_argv(char *str);
int				configure_io(char *str, t_cmd *cmdv);

// Executing
char			*get_path(char *cmd);
void			exec(t_cmd *cmdv);
int				launch_builtin(int *fd, t_cmd *cmdv, int i);
int				is_builtin(char *str);
void			set_child_fds(int fd[2], t_cmd *cmd);
void			set_fds(t_cmd *cmdv, int p[2], int fd[2], int i);

// Utils
int				max(int a, int b);
void			destroy_argv(char **argv);
void			destroy_cmd(t_cmd *cmdv);
void			destroy_cmdv(t_cmd *cmd);
void			print_cmdv(t_cmd *cmdv);
unsigned int	get_argv_size(char **argv);
int				get_cmd_size(t_cmd *cmdv);

// Prompt
char			*prompt_user(void);
char			*launch_hd(char *stop_str);

// Errors
void			print_error(char *prefix, char *error);
void			print_error_exit(char *prefix, char *error, int exit_code);

unsigned int	is_special_char(char c);
char			*get_qouted_str(char *str);
char			*get_regular_str(char *str);
int				*get_last_exit_p(void);
int				skip_redirect(const char *str, int *i);
int				skip_regular(const char *str, int *i);
int				skip_qouted(const char *str, int *i);
int				skip_arg(const char *str, int *i);
int				skip_non_arg(const char *str, int *i);

// Builtins
int				b_echo(t_cmd *cmd);
int				b_env(t_cmd *cmd);
int				b_export(t_cmd *cmd);
int				b_unset(t_cmd *cmd);
int				b_cd(t_cmd *cmd);
int				b_pwd(t_cmd *cmd);
int				b_exit(t_cmd *cmdv, int i);

// Env utils
int				validate_env(char *env);
int				add_env(char *env);
int				remove_env(char *env);
char			*get_env(char *env);

// Signals
void			disable_signals(void);
void			default_signals(void);
void			handle_cmd_signals(void);
void			handle_global_signals(void);
void			sig_hd(int sig);

#endif