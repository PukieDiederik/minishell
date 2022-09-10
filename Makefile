## File stuff

FNAMES 		=	minishell.c \
				\
				parsing/parsing.c \
				parsing/get_argv.c \
				parsing/cmd_count.c \
				parsing/argv_count.c \
				parsing/next_cmd.c \
				parsing/insert_env.c \
				parsing/configure_io.c \
				parsing/configure_io_handle.c \
				\
				parsing/print_cmdv.c \
				parsing/destroy_argvv.c \
				\
				prompt.c \
				here_doc.c \
				\
				execute.c \
				fds.c \
				utils.c \
				get_program_path.c \
				errors.c \
				builtins.c \
				\
				builtins/echo.c \
				builtins/env.c \
				builtins/export.c \
				builtins/unset.c \
				builtins/cd.c \
				builtins/pwd.c \
				builtins/exit.c \
				\
				env_utils/env_utils.c \
				env_utils/remove_env.c \
				env_utils/add_env.c \
				env_utils/get_env.c \
				utils/signal.c \
				utils/sig_hd.c \
				utils/sig_cmd.c \

SRCS		= 	$(addprefix $(SRCS_DIR)/,$(FNAMES))

OBJS		= 	$(addprefix $(OBJS_DIR)/,$(notdir $(FNAMES:.c=.o)))

INCLUDE_DIR	= include
SRCS_DIR	= src
OBJS_DIR	= obj
LIBFT		= libft/libft.a

## Compilation

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
INCLUDES	= -I $(INCLUDE_DIR) -I libft/include
LIBS		= -L libft -lft -lreadline
## Other

NAME		= minishell
RM			= rm -rf
MAKE		= make -s

ECHO		= echo -e


# Colors
BLACK			= \033[0;30m
RED				= \033[0;31m
GREEN			= \033[0;32m
ORANGE			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
GRAY			= \033[0;37m
WHITE			= \033[0;38m
RESET			= \033[0m


## Targets
all: $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@$(ECHO) "$(GREEN)>>>>> Compiling $(RESET)$(notdir $<)$(GREEN) -> $(RESET)$(notdir $@)$(RESET)"
	@gcc $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIR)/%.o : $(SRCS_DIR)/*/%.c
	@$(ECHO) "$(GREEN)>>>>> Compiling $(RESET)$(notdir $<)$(GREEN) -> $(RESET)$(notdir $@)$(RESET)"
	@gcc $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIR):
	@test -d $(OBJS_DIR) || (mkdir $(OBJS_DIR) && $(ECHO) "$(BLUE)Directory '$(CYAN)$(OBJS_DIR)/$(BLUE)' doesn't exist. Creating '$(CYAN)$(OBJS_DIR)/$(BLUE)'$(RESET)")

$(LIBFT):
	@$(MAKE) -C libft

# regular targets
$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@$(ECHO) "$(GREEN)>>>>> Linking <<<<<$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@$(ECHO) "$(GREEN)>>>>> Cleaning <<<<<$(RESET)"
	$(RM) $(OBJS)
	@$(ECHO) "Cleaning libft"
	@$(MAKE) -C libft clean

fclean: clean
	@$(ECHO) "Applying full clean"
	@$(RM) $(OBJS_DIR) $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

vars:
	@$(ECHO) "$(GREEN)CFLAGS: $(WHITE)$(CFLAGS)$(RESET)"
	@$(ECHO) "$(GREEN)CC: $(WHITE)$(CC)$(RESET)"
	@$(ECHO) "$(GREEN)FNAMES: $(WHITE)$(FNAMES)$(RESET)"
	@$(ECHO) "$(GREEN)SRCS: $(WHITE)$(SRCS)$(RESET)"
	@$(ECHO) "$(GREEN)OBJS: $(WHITE)$(OBJS)$(RESET)"
	@$(ECHO) "$(GREEN)HEADERS: $(WHITE)$(HEADERS)$(RESET)"

.PHONY: all clean fclean re
