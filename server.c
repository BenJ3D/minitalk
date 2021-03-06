/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:46:48 by bducrocq          #+#    #+#             */
/*   Updated: 2022/03/15 18:00:29 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

/**
 * @brief Filled str to form a binary string.
 * When the 8 bits are written, the char is ready.
 * Use ft_btoi function to convert
 * @param signal 
 */
void	sig_handler(int signal)
{
	if (signal == SIGUSR1)
		g_serv->str[g_serv->i] = '0';
	if (signal == SIGUSR2)
		g_serv->str[g_serv->i] = '1';
	g_serv->i += 1;
	if (g_serv->i == 8)
	{
		g_serv->str[g_serv->i] = '\0';
		g_serv->bin = BIN_OK_FOR_CHAR;
	}
}

/**
 * @brief processes the first 20 bits received
 * to determine the message size and the client pid.
 * 
 * @param pto tools struct pointer
 */
void	receive_first_parameters(t_tools *pto)
{	
	pto->c = ft_btoi(g_serv->str);
	pto->tmpsize[pto->y] = pto->c;
	g_serv->bin = BINARY_WAIT;
	g_serv->i = 0;
	if (pto->y == 9)
	{
		pto->size = ft_atoi(pto->tmpsize);
		pto->progress = GO_RECEIVE_MSG;
		pto->bool = TRUE;
		pto->y = 0;
		return ;
	}
	pto->y++;
}

/**
 * @brief 
 * 
 * @param ptr 
 */
int	initialize_var(t_tools	*ptr)
{
	static t_serv	ts;

	g_serv = &ts;
	g_serv->str = ft_calloc(sizeof(char), 9);
	if (!(g_serv->str))
		return (0);
	g_serv->i = 0;
	ptr->progress = WAIT_PARAMETER;
	ptr->y = 0;
	return (1);
}

/**
 * @brief Convert the binary string to int to fill the message variable.
 * Once the message is complete, displays the message
 * then free() the variable and send a signal to the client 
 * @param pto 
 */
void	write_message(t_tools	*pto)
{
	pto->c = ft_btoi(g_serv->str);
	pto->msg[pto->y] = pto->c;
	g_serv->bin = BINARY_WAIT;
	g_serv->i = 0;
	pto->y++;
	if (pto->y == pto->size)
	{
		pto->msg[pto->y] = '\0';
		ft_putstr_fd(pto->msg, 1);
		free(pto->msg);
		ft_putstr_fd("\n\n", 1);
		pto->progress = WAIT_PARAMETER;
		g_serv->bin = BINARY_WAIT;
		pto->y = 0;
	}
}

int	main(void)
{
	t_tools	to;
	t_tools	*pto;

	pto = &to;
	if (initialize_var(pto) == 0)
		return (0);
	printf("server PID: %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
	{
		pause();
		if (pto->progress == WAIT_PARAMETER && g_serv->bin == BIN_OK_FOR_CHAR)
			receive_first_parameters(pto);
		if (pto->progress == GO_RECEIVE_MSG && pto->bool == TRUE)
		{
			pto->msg = ft_calloc(pto->size + 1, sizeof(char));
			pto->y = 0;
			pto->bool = FALSE;
		}
		if (pto->progress == GO_RECEIVE_MSG && g_serv->bin == BIN_OK_FOR_CHAR)
			write_message(pto);
	}
	return (0);
}
