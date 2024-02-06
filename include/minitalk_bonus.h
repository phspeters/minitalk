/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:08:19 by pehenri2          #+#    #+#             */
/*   Updated: 2024/02/06 19:50:41 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft.h"
# include <signal.h>
# include <stdio.h>
# include <errno.h>

# define CONFIRMATION_SIGNAL 10
# define SIGNAL_EXCHANGE_SUCCESSFUL 12
# define BIT_ON 12
# define BIT_OFF 10

void	handle_error(char *message);
void	setup_signal_handler(struct sigaction *action, void (*func)(int signum,
				siginfo_t *info, void *context));
void	send_signal(int pid, int signal);

#endif
