/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/06 17:51:02 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>

	// if (ast->type == PIPE)
	// {
	// 	execute(ast->left);
	// 	execute(ast->right);
	// }
	// if (ast->type == STRING)
	// 	printf("->%s\n", ast->data->data);
void	execute(t_node *ast)
{
	execute_command(ast->data);
}

void	execute_command(t_token *command)
{
	int		status_code;
	pid_t	pid;
	int		comm[2];

	//TODO: here
	// if starts with /, check existence and permissions, and exec
	// else if it's a builtin, and exec
	// else check in the PATH dirs, check permissions, and exec
	// TODO: for PATH looking, is it the first match found or the last match?
	if (pipe(comm) == -1)
		action_failed("pipe");
	pid = fork();
	if (pid == -1)
		action_failed("fork");
	if (pid == 0)
		child_main(comm);
	else
	{
		encode(comm[1], command);
		waitpid(pid, &status_code, WUNTRACED); //TODO: make sure WUNTRACED is necessary, see man waitpid for maybe interesting macros
	}
}

void	child_main(int comm[2])
{
	char	**argv;
	char	**envp;

	argv = decode(comm[0]);
	envp = decode(comm[0]);
	if (execve(argv[0], argv, envp) == -1)
		action_failed("execve");
	// TODO: free?
}
