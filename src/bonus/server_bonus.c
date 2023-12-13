/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/13 11:48:45 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_total_bits_received = 0;

void	handle_termination_signal(int pid)
{
	if (pid)
		kill(pid, SIGUSR2);
	ft_printf("\nExiting server\nTotal bits received during runtime: %i \
bits (%i chars)\n", g_total_bits_received, (g_total_bits_received / 8));
	exit(EXIT_SUCCESS);
}

void	handle_client_signal(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bits_read = 0;
	static int				client_pid;

	(void)context;
	c = c << 1;
	bits_read++;
	if (signum == SIGUSR2)
		c = c | 1;
	if (bits_read == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		c = 0;
		bits_read = 0;
	}
	if (info->si_pid)
	{
		g_total_bits_received++;
		client_pid = info->si_pid;
	}
	if (signum == SIGTERM || signum == SIGQUIT || signum == SIGINT)
		handle_termination_signal(client_pid);
	send_signal(client_pid, CONFIRMATION_SIGNAL);
}

int	main(void)
{
	struct sigaction	action;

	setup_signal_handler(&action, handle_client_signal);
	if (sigaction(SIGUSR1, &action, NULL) == -1 || \
		sigaction(SIGUSR2, &action, NULL) == -1 || \
		sigaction(SIGINT, &action, NULL) == -1 || \
		sigaction(SIGQUIT, &action, NULL) == -1 || \
		sigaction(SIGTERM, &action, NULL) == -1)
	{
		handle_error("Error setting up signal handler");
	}
	ft_printf("Server PID: %i\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
