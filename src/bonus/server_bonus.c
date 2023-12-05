/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/04 22:10:11 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_signal(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0b11111111;
	static int				bits_read = 0;

	(void)context;
	if (signum == SIGUSR1)
		c ^= 0x80 >> bits_read;
	else if (signum == SIGUSR2)
		c |= 0x80 >> bits_read;
	c = c << 1;
	bits_read++;
	if (bits_read % 8 == 0)
	{
		if (c)
		{
			write(STDOUT_FILENO, &c, 1);
			c = 0b11111111;
		}
		else
		{
			bits_read = 0;
			c = 0b11111111;
			return ;
		}
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		return ;
}

//ft_printf("Received %i bits (%i bytes) from client\n", bits_read, (bits_read / 8));
int	main(void)
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_flags = SA_RESTART | SA_SIGINFO;
	action.sa_sigaction = &handle_client_signal;
	if (sigaction(SIGUSR1, &action, NULL) == -1 || sigaction(SIGUSR2, &action, NULL) == -1)
	{
		perror("Signal");
		exit(errno);
	}
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
