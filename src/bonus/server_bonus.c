/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:19:15 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/06 19:50:14 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/**
 * @brief Global variable to store the total bits received during runtime.
 */
int	g_total_bits_received = 0;

/**
 * @brief Function to handle the SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) signals.
 * It prints the total bits received during runtime and exits the program with
 * EXIT_SUCCESS status.
 * 
 * @param signum Signal number. In this case, SIGINT or SIGQUIT.
 * @param info Not used in this function.
 * @param context Not used in this project.
 */
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

/**
 * @brief Handles the signal sent by the client. It reads the signal and decodes
 * it in either a bit off (0) or bit on (1) and stores it in a static variable.
 * After that, it sends a SIGUSR1 back to the client, as a confirmation signal
 * indicating it's ready to receive the next signal.
 * When 8 bits are read, it prints the character and resets the static variable,
 * unless the character is a newline, in which case it sends a SIGUSR2 to the
 * client to indicate that the exchange was successful.
 * 
 * @param signum The signal number. In this case, SIGUSR1 or SIGUSR2.
 * @param info The signal information. Contains the client's process ID.
 * @param context The signal context. Not used in this project.
 */
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

/**
 * @brief The main function of the server program. It sets the action to be
 * taken when a signal is received and installs the signal handler. It then
 * prints it's PID and wait for signals until the process is stopped.
 * 
 * @param action The struct required by the sigaction function that will handle
 * the SIGUSR1 and SIGUSR2 signals. It holds the function to be called when
 * a specific signal is received as well as other information.
 * @param termination The struct required by the sigaction function that will
 * handle the SIGINT and SIGQUIT signals. It holds the function to be called when
 * a specific signal is received as well as other information.
 * @param handle_client_signal The function that will handle the signal.
 */
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
