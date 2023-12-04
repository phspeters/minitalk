/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:58:43 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/04 15:33:44 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_str_to_server(int pid, char *str)
{
	int		bit_index;

	while (*str)
	{
		bit_index = 0;
		while (bit_index < 8)
		{
			if ((*str << bit_index) & 0b10000000)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(200);
			bit_index++;
		}
		str++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;

	if (argc != 3)
		return (1);
	server_pid = ft_atoi(argv[1]);
	send_str_to_server(server_pid, argv[2]);
	send_str_to_server(server_pid, "\n");
}
