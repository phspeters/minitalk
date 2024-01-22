/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:08:19 by pehenri2          #+#    #+#             */
/*   Updated: 2024/01/22 13:03:42 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <errno.h>

# define CONFIRMATION_SIGNAL 0
# define SIGNAL_EXCHANGE_SUCCESSFUL 1
# define BIT_ON 1
# define BIT_OFF 0

void	handle_error(char *message);
void	setup_signal_handler(struct sigaction *action, void (*func)(int signum,
				siginfo_t *info, void *context));
int		send_signal(int pid, int signal);

#endif
