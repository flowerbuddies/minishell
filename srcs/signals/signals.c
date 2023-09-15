/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:56:58 by hunam             #+#    #+#             */
/*   Updated: 2023/09/15 16:15:19 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

void	sig_interactive_mode(int signal)
{
	(void) signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	get_shell()->exit_status = failure;
	(void) signal;
}

void	sig_non_interactive_mode(int signal)
{
	if (signal == SIGINT)
		get_shell()->sigint = true;
	else
		get_shell()->sigquit = true;
	get_shell()->exit_status = signal_base + signal;
}

void	sig_heredoc_mode(int signal)
{
	(void) signal;
	get_shell()->heredoc_exited = true;
	close(STDIN_FILENO);
}
