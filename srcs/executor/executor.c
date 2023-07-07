/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 17:28:49 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "libft.h"
#include "builtin.h"

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
	int			status_code;
	pid_t		pid;
	int			comm[2];
	char		*path;
	struct stat	path_stat;

	if (ft_strchr(command->data, '/'))
	{
		if (access(command->data, F_OK) == -1)
		{
			printf("\e[31;1mError:\e[0m command `%s` not found\n", command->data);
			set_last_exit_status(not_found);
			return ;
		}
		else if (access(command->data, X_OK) == -1)
		{
			printf("\e[31;1mError:\e[0m permission denied on `%s`\n",
				command->data);
			set_last_exit_status(not_executable);
			return ;
		}
		else
		{
			if (stat(command->data, &path_stat) == -1)
				action_failed("stat");
			if (!S_ISREG(path_stat.st_mode))
			{
				printf("\e[31;1mError:\e[0m `%s` is not a file\n", command->data);
				set_last_exit_status(not_executable);
				return ;
			}
			path = ft_strdup(command->data);
		}
	}
	else if (is_builtin(command->data))
		return (execute_builtin(command->data));
	else
	{
		path = find_cmd_in_path(command->data);
		if (!path)
		{
			printf("\e[31;1mError:\e[0m command `%s` not found\n", command->data);
			set_last_exit_status(not_found);
			return ;
		}
	}
	if (pipe(comm) == -1)
		action_failed("pipe");
	pid = fork();
	if (pid == -1)
		action_failed("fork");
	if (pid == 0)
		child_main(comm);
	else
	{
		encode(comm[1], path, command);
		free(path);
		waitpid(pid, &status_code, WUNTRACED); //TODO: make sure WUNTRACED is necessary, see man waitpid for maybe interesting macros
	}
}

void	child_main(int comm[2])
{
	if (execve(decode_string(comm[0]), decode_array(comm[0]),
			decode_array(comm[0])) == -1)
		action_failed("execve");
}
