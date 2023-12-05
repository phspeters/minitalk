/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:58:43 by pehenri2          #+#    #+#             */
/*   Updated: 2023/12/04 22:23:57 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_error(char *str)
{
	if (str)
		free (str);
	exit(EXIT_FAILURE);
}

int	send_message_end(int pid, char *str)
{
	static int	bits_sent = 0;
	static char	*end = "\n\0";

	if (bits_sent < 16)
	{
		if ((*end << (bits_sent % 8)) & 0b10000000)
		{
			if (kill(pid, SIGUSR2) == -1)
				handle_client_error(str);
		}
		else
			if (kill(pid, SIGUSR1) == -1)
				handle_client_error(str);
		bits_sent++;
		return (0);
	}
	return (bits_sent);
}

int	send_bit(int server_pid, char *str)
{
	static int	bits_sent = 0;
	static char	*message;

	if (str)
		message = ft_strdup(str);
	if (!message)
		handle_client_error(message);
	if (message[bits_sent / 8])
	{
		if ((message[bits_sent / 8] << (bits_sent % 8)) & 0b10000000)
		{
			if (kill(server_pid, SIGUSR2) == -1)
				handle_client_error(message);
		}
		else
			if (kill(server_pid, SIGUSR1) == -1)
				handle_client_error(message);
		bits_sent++;
		return (0);
	}
	if (!send_message_end(server_pid, message))
		return (0);
	bits_sent += 16;
	free(message);
	exit(ft_printf("Sent %i bits (%i bytes) to server\n", bits_sent, (bits_sent / 8)));
}

void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		send_bit(info->si_pid, 0);
	else if (signum == SIGUSR2)
		handle_client_error(NULL);
}

int	main(int argc, char *argv[])
{
	struct sigaction	action;

	if (argc != 3)
		return (write(STDOUT_FILENO, "Correct usage: ./client 'Server PID' 'message'\n", 47));
	ft_bzero(&action, sizeof(struct sigaction));
	action.sa_flags = SA_RESTART | SA_SIGINFO;
	action.sa_sigaction = &handle_server_signal;
	if (sigaction(SIGUSR1, &action, NULL) == -1 || sigaction(SIGUSR2, &action, NULL) == -1)
		return (write(STDOUT_FILENO, "Error setting up signal handler\n", 32));
	send_bit(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
}
