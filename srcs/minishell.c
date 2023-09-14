/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 19:25:17 by hunam            ###   ########.fr       */
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
	eprintf("\e[31;1mError\e[0m: \e[4m%s\e[0m failed. %s\n",
		action, strerror(errno));
	exit(1);
}

bool	streq(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);

	return (s1_len == (int)ft_strlen(s2) && ft_strncmp(s1, s2, s1_len) == 0);
}

void	eprintf(const char *s1, const char *s2, const char *s3)
{
	const int	dupped_stdout = dup(STDOUT_FILENO);

	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(s1, s2, s3);
	dup2(dupped_stdout, STDOUT_FILENO);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	rl_catch_signals = 0;
	g_shell.exit_status = 0;
	g_shell.sigint = false;
	g_shell.sigquit = false;
	g_shell.heredoc_exited = false;
	g_shell.exit_needed = false;
	init_env_vars(ev);
	prompt();
}
