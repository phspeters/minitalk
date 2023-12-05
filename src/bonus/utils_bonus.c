/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:47:20 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/05 18:08:24 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_error(char *message)
{
	if (errno)
	{
		perror(message);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "%s.\n", message);
		exit(EXIT_FAILURE);
	}
}

void	setup_signal_handler(struct sigaction *action, void (*func)(int signum,
	siginfo_t *info, void *context))
{
	ft_bzero(action, sizeof(struct sigaction));
	action->sa_flags = SA_RESTART | SA_SIGINFO;
	action->sa_sigaction = func;
}

int	send_signal(int pid, int signal)
{
	if (signal == 1 || signal == SIGUSR2)
	{
		if (kill(pid, SIGUSR2) == -1)
			handle_error("Error sending signal");
	}
	else if (signal == 0 || signal == SIGUSR1)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error("Error sending signal");
	}
	return (EXIT_SUCCESS);
}
