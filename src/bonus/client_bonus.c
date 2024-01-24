/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:58:43 by pehenri2          #+#    #+#             */
/*   Updated: 2024/01/24 15:37:58 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_server_signal_received = 0;

void	send_newline_to_server(int pid)
{
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		g_server_signal_received = 0;
		if (('\n' >> bit_index) & 1)
			send_signal(pid, BIT_ON);
		else
			send_signal(pid, BIT_OFF);
		bit_index--;
		while (!g_server_signal_received)
			;
	}
}

void	send_string_to_server(int pid, char *str)
{
	int		bit_index;
	int		total_bits_sent;

	total_bits_sent = 0;
	while (*str)
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			g_server_signal_received = 0;
			if ((*str >> bit_index) & 1)
				send_signal(pid, BIT_ON);
			else
				send_signal(pid, BIT_OFF);
			bit_index--;
			total_bits_sent++;
			while (!g_server_signal_received)
				;
		}
		str++;
	}
	ft_printf("\nTotal bits sent to server: %i bits (%i chars)\n", \
	total_bits_sent, (total_bits_sent / 8));
	send_newline_to_server(pid);
}

void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		g_server_signal_received = 1;
	if (signum == SIGUSR2)
	{
		ft_printf("Communication successful: exiting client\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	action;
	int					server_pid;

	if (argc != 3)
		handle_error("Correct usage: ./client 'Server PID' 'message'");
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		handle_error("Cannot reach server");
	setup_signal_handler(&action, handle_server_signal);
	if (sigaction(SIGUSR1, &action, NULL) == -1 || \
		sigaction(SIGUSR2, &action, NULL) == -1)
		handle_error("Error setting up signal handler");
	send_string_to_server(server_pid, argv[2]);
	return (EXIT_SUCCESS);
}
