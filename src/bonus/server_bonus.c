/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2024/01/26 10:08:25 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int	g_total_bits_received = 0;

void	handle_termination_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT || signum == SIGQUIT)
	{
		ft_printf("\n\tExiting server\n\tTotal bits received during runtime: %i \
bits (%i chars)\n", g_total_bits_received, (g_total_bits_received / 8));
		exit(EXIT_SUCCESS);
	}
}

void	handle_client_signal(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				bits_read;
	int						client_pid;

	(void)context;
	client_pid = info->si_pid;
	bits_read++;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	if (bits_read == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		if (c == '\n')
			send_signal(client_pid, SIGNAL_EXCHANGE_SUCCESSFUL);
		else
			g_total_bits_received += bits_read;
		c = 0;
		bits_read = 0;
	}
	send_signal(client_pid, CONFIRMATION_SIGNAL);
}

int	main(void)
{
	struct sigaction	client;
	struct sigaction	termination;

	setup_signal_handler(&client, handle_client_signal);
	setup_signal_handler(&termination, handle_termination_signal);
	if (sigaction(SIGUSR1, &client, NULL) == -1 || \
		sigaction(SIGUSR2, &client, NULL) == -1 || \
		sigaction(SIGINT, &termination, NULL) == -1 || \
		sigaction(SIGQUIT, &termination, NULL) == -1)
	{
		handle_error("Error setting up signal handler");
	}
	ft_printf("Server PID: %i\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
