/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/03 19:45:17 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_signal(int signum)
{
	static unsigned char	c = 0;
	static int				bits_read = 0;

	c = c << 1;
	if (signum == SIGUSR1)
		c = c | 1;
	bits_read++;
	if (bits_read == 8)
	{
		write(STDOUT_FILENO, &c, 1);
		bits_read = 0;
		c = 0;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	if (signal(SIGUSR1, handle_client_signal) == SIG_ERR || signal(SIGUSR2, handle_client_signal) == SIG_ERR)
	{
		perror("Signal");
		exit(errno);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
