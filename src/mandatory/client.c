/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:21 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/02 09:28:44 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_str_to_server(int pid, char *str)
{
	int		i;

	while (*str)
	{
		i = 0;
		while (i < 8)
		{
			if ((*str >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			i++;
		}
		str++;
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR2);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
		return (1);
	server_pid = ft_atoi(argv[1]);
	send_str_to_server(server_pid, argv[2]);
}
