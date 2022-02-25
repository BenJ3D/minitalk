/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:05:16 by bducrocq          #+#    #+#             */
/*   Updated: 2022/02/25 15:05:53 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minitalk.h"

int	main(int ac, char **av)
{
	int	pid;

	pid = atoi(av[1]);
	if (*av[2] == '1')
	{
		printf("sig 1");
		kill(pid, SIGUSR1); 
	}
	if (*av[2] == '2')
	{
		printf("sig 2");
		kill(pid, SIGUSR2);
	}
	if (*av[2] == '0')
	{
		printf("sig 0");
		kill(pid, SIGSTOP);
	}
	return (0);
}