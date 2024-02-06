/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/06 19:51:16 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * @brief The function that handles the SIGUSR1 and SIGUSR2 signals sent by the
 * client. It reads the signal and decodes it in either a bit off (0) or bit on
 * (1) and stores it in a static variable. After that, it sends a SIGUSR1 back
 * to the client, as a confirmation signal indicating it's ready to receive the
 * next signal. When 8 bits are read, it prints the character and resets the
 * static variable.
 * 
 * @param signum The signal number. In this case, SIGUSR1 or SIGUSR2.
 * @param info The signal information. Contains the client's process ID.
 * @param context The signal context. Not used in this project.
 */
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

/**
 * @brief The main function of the server program. It sets the action to be
 * taken when a signal is received and installs the signal handler. It then
 * prints it's PID and wait for signals until the process is stopped.
 * 
 * @param action The struct required by the sigaction function that will handle
 * the SIGUSR1 and SIGUSR2 signals. It holds the function to be called when
 * a specific signal is received as well as other information.
 * @param handle_client_signal The function that will handle the signal.
 */
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
