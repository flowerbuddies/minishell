/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 18:20:10 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"

void	execute(t_node *ast)
{
	execute_command(ast->data);
}

void	execute_command(t_token *command)
{
	int			status_code;
	pid_t		pid;
	int			comm[2];
	const char	*path = get_command_path(command->data);

	if (!path)
		return ;
	if (pipe(comm) == -1)
		action_failed("pipe");
	pid = fork();
	if (pid == -1)
		action_failed("fork");
	if (pid == 0)
		child_main(comm);
	else
	{
		encode(comm[1], (char *) path, command);
		free((char *) path);
		waitpid(pid, &status_code, WUNTRACED); //TODO: make sure WUNTRACED is necessary, see man waitpid for maybe interesting macros
	}
}

void	child_main(int comm[2])
{
	if (execve(decode_string(comm[0]), decode_array(comm[0]),
			decode_array(comm[0])) == -1)
		action_failed("execve");
}
