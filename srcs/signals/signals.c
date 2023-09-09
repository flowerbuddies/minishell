/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:56:58 by hunam             #+#    #+#             */
/*   Updated: 2023/09/09 20:15:12 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <readline/readline.h>
#include "minishell.h"

void	sig_interactive_mode(int signal)
{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.exit_status = failure;
}

void	sig_non_interactive_mode(int signal)
{
	g_shell.nl_needed = true;
	g_shell.exit_status = signal_base + signal;
}
