#include <minishell.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

static int	is_empty_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

static int	is_empty(char *str)
{
	while (str && *str && is_empty_char(*str))
		str++;
	return (!(str && !is_empty_char(*str)));
}

char	*prompt_user(void)
{
	char	*str;

	str = 0;
	while (is_empty(str))
	{
		free(str);
		str = readline(C_GREEN"$"C_CYAN">"C_RESET);
	}
	add_history(str);
	return (str);
}
