/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:56:58 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 18:22:10 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <signal.h>
#include "minishell.h"

static void	sigint_handler(int signal)
{
	if (g_shell.is_child_running)
	{
		g_shell.stop_child = true;
		if (kill(g_shell.child_pid, SIGINT) == -1)
			action_failed("kill");
		g_shell.exit_status = signal_base + signal;
	}
	else
	{
		ft_printf("here should give a new line\n");
		g_shell.exit_status = failure;
	}
}

static void	sigquit_handler(int signal)
{
	if (g_shell.is_child_running)
	{
		g_shell.stop_child = true;
		if (kill(g_shell.child_pid, SIGQUIT) == -1)
			action_failed("kill");
		g_shell.exit_status = signal_base + signal;
	}
}

void	init_signals(void)
{
	g_shell.is_child_running = false;
	g_shell.stop_child = false;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
