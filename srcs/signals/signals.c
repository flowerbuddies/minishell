/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:56:58 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 15:37:16 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

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
	get_shell()->nl_needed = true;
	get_shell()->exit_status = signal_base + signal;
}
