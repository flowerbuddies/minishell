/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:56:58 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 18:02:52 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include <signal.h>

void	sig_interactive_mode(int signal)
{
	(void) signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.exit_status = failure;
	(void) signal;
}

void	sig_non_interactive_mode(int signal)
{
	if (signal == SIGINT)
		g_shell.sigint = true;
	else
		g_shell.sigquit = true;
	g_shell.exit_status = signal_base + signal;
}

void	sig_heredoc_mode(int signal)
{
	(void) signal;
	g_shell.heredoc_exited = true;
	close(STDIN_FILENO);
}
