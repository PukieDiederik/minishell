## File stuff

FNAMES 		=	minishell.c \
				\
				parsing/parsing.c \
				parsing/cmd_count.c \
				parsing/argv_count.c \
				parsing/next_cmd.c \
				parsing/insert_env.c \
				\
				parsing/print_argvv.c \
				parsing/destroy_argvv.c

SRCS		= 	$(addprefix $(SRCS_DIR)/,$(FNAMES))

OBJS		= 	$(addprefix $(OBJS_DIR)/,$(notdir $(FNAMES:.c=.o)))

INCLUDE_DIR	= include
SRCS_DIR	= src
OBJS_DIR	= obj
LIBFT		= libft/libft.a

## Compilation

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
INCLUDES	= -I $(INCLUDE_DIR) -I libft
LIBS		= -L libft -lft
## Other

NAME		= minishell
RM			= rm -rf
MAKE		= make -s
# Echo (Different on Linux and Mac)
ifeq ($(shell uname),Linux)
	ECHO	= echo -e
else
	ECHO	= echo
endif


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
	@$(MAKE) -C libft bonus

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
	@echo "$(GREEN)CFLAGS: $(WHITE)$(CFLAGS)$(RESET)"
	@echo "$(GREEN)CC: $(WHITE)$(CC)$(RESET)"
	@echo "$(GREEN)FNAMES: $(WHITE)$(FNAMES)$(RESET)"
	@echo "$(GREEN)SRCS: $(WHITE)$(SRCS)$(RESET)"
	@echo "$(GREEN)OBJS: $(WHITE)$(OBJS)$(RESET)"

.PHONY: all clean fclean re
