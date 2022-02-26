#ifndef MINITALK_H
# define MINITALK_H

# include "ft_printf.h"
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <signal.h>

enum	state
{
	NOT_FINISH,
	FINISH
};

typedef struct s_utils
{
	int	i;
	int	bool;
	char str[8];
	enum state progress;
}	t_utils;

static t_utils	tu;

char	*ft_atob(char c);
void	sig_handler1();
void	sig_handler2();
void	ft_sendbin(char *str, int pid, int i);
int		ft_btoi(char *str);


#endif