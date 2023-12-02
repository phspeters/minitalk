/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2023/11/30 21:18:44 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = &handle_client_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	handle_client_signal(int signum, siginfo_t *info, void *context)
{
	
}
