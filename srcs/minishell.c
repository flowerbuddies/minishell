/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 15:35:01 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "executor.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "signals.h"

void	action_failed(char *action)
{
	printf("\e[31;1mError\e[0m: \e[4m%s\e[0m failed. %s\n", action, strerror(errno));
	exit(1);
}

bool	streq(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);

	return (s1_len == (int)ft_strlen(s2) && ft_strncmp(s1, s2, s1_len) == 0);
}

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	rl_catch_signals = 0;
	get_shell()->exit_status = 0; // TODO: static already init to 0?
	get_shell()->nl_needed = false;
	get_shell()->exit_needed = false;
	init_env_vars(ev);
	prompt();
}
