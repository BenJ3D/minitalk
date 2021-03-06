/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:05:16 by bducrocq          #+#    #+#             */
/*   Updated: 2022/03/15 17:42:54 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk_bonus.h"

/**
 * @brief send message in binary
 * 
 * @param str string to send
 * @param pid pid server
 * @param speed speed usleep sending signal 
 * 	(100 by default, some mac break with less)
 */
void	ft_sendbin(char *str, int pid, int speed)
{
	char	*tmp;
	int		j;
	int		i;

	i = 0;
	while (str[i])
	{
		tmp = ft_atob(str[i]);
		j = 0;
		while (tmp[j])
		{
			if (tmp[j] == '0')
				kill(pid, SIGUSR1);
			if (tmp[j] == '1')
				kill(pid, SIGUSR2);
			usleep(speed);
			j++;
		}
		i++;
		free(tmp);
	}
}

/**
 * @brief int to str with x $count char
 * (ex int = 4242 count = 10 return str : 0000004242)
 * (!free str!)
 * @param size 	l'int a formater en str
 * @param count 
 * @return char* 
 */
char	*ft_imax_to_str(int size, int count)
{
	t_tools	to;

	to.str = ft_calloc(count + 1, sizeof(char));
	if (!to.str)
		return (NULL);
	to.y = count - 1;
	ft_memset(to.str, '0', count);
	to.tmp = ft_itoa(size);
	to.i = ft_strlen(to.tmp) - 1;
	while (to.i >= 0)
		to.str[to.y--] = to.tmp[to.i--];
	free(to.tmp);
	return (to.str);
}

void	signal_handler_client(int signal)
{
	if (signal == SIGUSR1)
	{
		g_msg_ok = TRUE;
		ft_putstr_fd("The message has been received by the server\n", 1);
	}
}

int	send_size_and_pid(t_tools *ptc)
{
	ft_sendbin(ptc->str, ptc->pid, 400);
	free(ptc->str);
	ptc->str = ft_imax_to_str((int)getpid(), 10);
	if (!(ptc->str))
		return (0);
	ft_sendbin(ptc->str, ptc->pid, 400);
	free(ptc->str);
	return (1);
}

int	main(int ac, char **av)
{
	t_tools	tc;
	t_tools	*ptc;

	if (ac != 3)
		return (printf("Please enter PID SERVER and \"MESSAGE\"\n"));
	ptc = &tc;
	ptc->pid = ft_atoi(av[1]);
	g_msg_ok = FALSE;
	ptc->str = ft_imax_to_str(ft_strlen(av[2]), 10);
	if (!(ptc->str))
		return (0);
	send_size_and_pid(ptc);
	ft_sendbin(av[2], ptc->pid, SPEED);
	usleep(100);
	signal(SIGUSR1, signal_handler_client);
	while (g_msg_ok != TRUE)
		pause();
	return (0);
}
