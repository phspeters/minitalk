/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:58:43 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/06 19:41:52 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/**
 * @brief Global variable to indicate if a signal was received. Works as a 
 * semaphore in this context.
 */
int	g_server_signal_received = 0;

/**
 * @brief Encodes a string into bits and sends signals to the server with
 * the kill function. Sends SIGUSR1 for bit off (0) and SIGUSR2 for bit on (1).
 * The function iterates through the string and for each character, it iterates
 * through the bits of the character, sending a signal for each bit.
 * After sending a signal, it waits for the server to send a signal back to
 * indicate that it received the signal.
 * When the all the string is sent, it prints the total number of bits and bytes
 * sent.
 * 
 * @param pid The server's process ID.
 * @param str The string to be sent. It will first be encoded into bits and then
 * signals that will be sent to the server.
 */
void	send_string_to_server(int pid, char *str)
{
	int		bit_index;
	int		total_bits_sent;

	total_bits_sent = 0;
	while (*str)
	{
		bit_index = 7;
		while (bit_index >= 0)
		{
			g_server_signal_received = 0;
			if ((*str >> bit_index) & 1)
				send_signal(pid, BIT_ON);
			else
				send_signal(pid, BIT_OFF);
			bit_index--;
			total_bits_sent++;
			while (!g_server_signal_received)
				;
		}
		str++;
	}
	ft_printf("\tTotal bits sent to server: %i bits (%i bytes)\n", \
	total_bits_sent, (total_bits_sent / 8));
}

/**
 * @brief Handles the signal sent back by the server. If it receives SIGUSR1, it
 * sets the global variable g_server_signal_received to 1. If it receives
 * SIGUSR2, it prints a message indicating the communication was successful and
 * exits the client with EXIT_SUCCESS status.
 * 
 * @param signum The signal number. In this case, SIGUSR1.
 * @param info The signal information. Not used in the mandatory part of the
 * project.
 * @param context The signal context. Not used in this project.
 */
void	handle_server_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		g_server_signal_received = 1;
	if (signum == SIGUSR2)
	{
		ft_printf("\tCommunication successful: exiting client\n");
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief Main function of the client. It first checks if the correct number of
 * arguments was passed. Then it checks if the server is reachable. If it is,
 * it sets up the signal handler to handle the confirmation signal and sends
 * the message to the server followed by a newline.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The arguments passed to the program.
 * @param handle_server_signal The function that will handle the signal sent back
 * by the server.
 * @return int Returns EXIT_FAILURE if the program reaches the end of the main
 * function without receiving a SIGUSR2 from the server.
 */
int	main(int argc, char *argv[])
{
	struct sigaction	server;
	int					server_pid;

	if (argc != 3)
		handle_error("Correct usage: ./client 'Server PID' 'message'");
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		handle_error("Cannot reach server");
	setup_signal_handler(&server, handle_server_signal);
	if (sigaction(SIGUSR1, &server, NULL) == -1 || \
		sigaction(SIGUSR2, &server, NULL) == -1)
		handle_error("Error setting up signal handler");
	send_string_to_server(server_pid, argv[2]);
	send_string_to_server(server_pid, "\n");
	return (EXIT_FAILURE);
}
