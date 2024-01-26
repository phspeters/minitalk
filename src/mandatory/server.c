/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2024/01/26 09:51:30 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_signal(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bits_read = 0;

	(void)context;
	c = c << 1;
	if (signum == SIGUSR2)
		c = c | 1;
	bits_read++;
	if (bits_read == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		c = 0;
		bits_read = 0;
	}
	send_signal(info->si_pid, CONFIRMATION_SIGNAL);
}

int	main(void)
{
	struct sigaction	action;

	setup_signal_handler(&action, handle_client_signal);
	if (sigaction(SIGUSR1, &action, NULL) == -1 || \
		sigaction(SIGUSR2, &action, NULL) == -1)
		handle_error("Error setting up signal handler");
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
