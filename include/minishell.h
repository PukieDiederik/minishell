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

# define SET_EXIT_STATUS(x) ((x) << 8)

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
 * str			- Takes the raw string of the command
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

// Executing
char			*get_path(char *cmd);
int				exec(t_cmd *cmdv, char **envp);
int				launch_builtin(int *fd, t_cmd *cmdv, int i);
int				is_builtin(char *str);
void			set_child_fds(int fd[2], t_cmd *cmd);

// Utils
void			destroy_argv(char **argv);
void			destroy_cmd(t_cmd *cmdv);
void			destroy_cmdv(t_cmd *cmd);
void			print_cmdv(t_cmd *cmdv);
unsigned int	get_argv_size(char **argv);

// Prompt
char			*prompt_user(void);
char			*here_doc(char *stop_str);

// Errors
void			print_error(char *prefix, char *error);
void			print_error_exit(char *prefix, char *error, int exit_code);


unsigned int	is_special_char(char c);
char			*get_qouted_str(char *str);
char			*get_regular_str(char *str);
int				skip_redirect(char *str, int *i);
int				*get_last_exit_p(void);

// Builtins
int				b_echo(t_cmd *cmd);
int				b_env(t_cmd *cmd);
int				b_export(t_cmd *cmd);
int				b_unset(t_cmd *cmd);

// Env utils
int	add_env(char *env);
int	remove_env(char *env);
int validate_env(char *env);


// Env stuff
//char			*env_to_str(t_env *lst);
//int				env_init(t_mini *mini, char **env_array);
//int				secret_env_init(t_mini *mini, char **env_array);
//char			*get_env_value(char *arg, t_env *env);
//char			*env_value(char *env);
//int				env_value_len(const char *env);
//int				is_env_char(int c);
//int				is_valid_env(const char *env);
//void			print_sorted_env(t_env *env);
//size_t			size_env(t_env *lst);


// Signal stuff
//void			sig_int(int code);
//void			sig_quit(int code);
//void			sig_init(void);

#endif