/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:58:43 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/14 16:45:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_server_signal_received = 0;

void	send_string_to_server(int pid, char *str)
{
	int		bit_index;

	while (*str)
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			g_server_signal_received = 0;
			if ((*str >> bit_index) & 1)
				send_signal(pid, 1);
			else
				send_signal(pid, 0);
			bit_index--;
			while (!g_server_signal_received)
				;
		}
		str++;
	}
}

void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		g_server_signal_received = 1;
}

int	main(int argc, char *argv[])
{
	struct sigaction	action;
	int					server_pid;

	if (argc != 3)
		handle_error("Correct usage: ./client 'Server PID' 'message'");
	setup_signal_handler(&action, handle_server_signal);
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		handle_error("Error setting up signal handler");
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1)
		handle_error("Cannot reach server");
	send_string_to_server(server_pid, argv[2]);
	return (EXIT_SUCCESS);
}
