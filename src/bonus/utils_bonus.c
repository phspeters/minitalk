/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:47:20 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/06 19:32:38 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/**
 * @brief Handles the error message. If errno is set, it prints the error message
 * using perror. Otherwise, it prints the message using ft_fprintf.
 * 
 * @param message The error message to be printed.
 */
void	handle_error(char *message)
{
	if (errno)
	{
		perror(message);
		exit(errno);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "%s\n", message);
		exit(EXIT_FAILURE);
	}
}

/**
 * @brief Sets up the signal handler. It initialises the struct memory range as 
 * zero to avoid conflicts because some members of the struct are interpreted as 
 * flags. It then turns on the SA_SIGINFO flag, indicating to the sigaction 
 * function to use the (*sa_sigaction) member instead of the default 
 * (*sa_handler) as the handler. That gives access to the siginfo_t struct by
 * the handler, which contains the sender's PID. 
 * 
 * @param action The struct required by the sigaction function. It holds the
 * action to be taken when a signal is received and other information.
 * @param func The function that will handle the signal and be stored inside the
 * struct sigaction.
 */
void	setup_signal_handler(struct sigaction *action, void (*func)(int signum,
	siginfo_t *info, void *context))
{
	ft_bzero(action, sizeof(struct sigaction));
	action->sa_flags = SA_SIGINFO;
	action->sa_sigaction = func;
}

/**
 * @brief Sends either SIGUSR1 or SIGUSR2 to a process. It uses the kill
 * function to send the signal to the process with the given PID. Also, it
 * checks if the signal was sent successfully and handles the error if it wasn't.
 * 
 * @param pid The process ID of the process that will receive the signal.
 * @param signal The signal to be sent.
 */
void	send_signal(int pid, int signal)
{
	if (signal == SIGUSR2)
	{
		if (kill(pid, SIGUSR2) == -1)
			handle_error("Error sending signal");
	}
	else if (signal == SIGUSR1)
	{
		if (kill(pid, SIGUSR1) == -1)
			handle_error("Error sending signal");
	}
}
