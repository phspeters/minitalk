/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/01 20:40:42 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_signal(int signum)
{
	static char	c;
	static int	bits_read;

	if (signum == SIGUSR1)
	{
		c = c | 1;
		c = c << 1;
		bits_read++;
	}
	else if (signum == SIGUSR2)
	{
		c = c << 1;
		bits_read++;
	}
	if (bits_read == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		bits_read = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_client_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
