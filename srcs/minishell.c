/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/07/05 17:21:51 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "executor.h"
#include <unistd.h>

//TODO: use errno to indicate the error, probably strerror or perror too
void	action_failed(char *action)
{
	ft_printf("\e[31;1mError\e[0m: \e[4m%s\e[0m failed\n", action);
	exit(1);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	if (pipe(g_shell.pipe_ends) == -1)
		action_failed("pipe");
	g_shell.child_pid = fork();
	if (g_shell.child_pid == -1)
		action_failed("fork");
	else if (g_shell.child_pid == 0)
	{
		printf("child main\n");
		child_main();
	}
	else
	{
		printf("parent main\n");
		init_env_vars(ev);
		prompt();
	}
}
