/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/07/03 18:39:20 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "executor.h"
#include <unistd.h>

void	action_failed(char *action)
{
	ft_printf("\e[31;1mError\e[0m: \e[4m%s\e[0m failed\n", action);
	exit(1);
}

int	main(int ac, char **av, char **ev)
{
	pid_t	pid;

	(void) ac;
	(void) av;
	if (pipe(g_shell.pipe_ends) == -1)
		action_failed("pipe");
	pid = fork();
	if (pid == -1)
		action_failed("fork");
	else if (pid == 0)
		child_main();
	else
	{
		init_env_vars(ev);
		prompt();
	}
}
