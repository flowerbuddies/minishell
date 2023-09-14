/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 15:37:16 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "builtin.h"

void	execute(t_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == PIPE)
		return (execute_pipe(ast));
	return (execute_command(ast));
}

void	execute_command(t_node *node)
{
	char		*path;
	const bool	is_a_builtin = is_builtin(node->token);

	if (is_a_builtin)
		execute_builtin(node->token, true);
	else
	{
		path = get_command_path(node->token->data);
		if (!path)
			return ;
	}
	if (fork() == 0)
	{
		// error
		if (!execute_redir(node->redirs))
			exit(get_shell()->exit_status);
		if (is_a_builtin)
			(execute_builtin(node->token, false), exit(get_shell()->exit_status));
		if (execve(path, get_argv(node->token), get_envp(get_shell()->vars))
			== -1)
			action_failed("execve");
	}
	if (!is_a_builtin)
		free((char *)path);
	wait((int *)&get_shell()->exit_status);
	if (WIFSIGNALED(get_shell()->exit_status))
		get_shell()->exit_status = signal_base + WTERMSIG(get_shell()->exit_status);
	else
		get_shell()->exit_status = WEXITSTATUS(get_shell()->exit_status);
}

void	execute_pipe(t_node *node)
{
	pid_t	pip[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_code;

	if (pipe(pip) == -1)
		action_failed("pipe");
	pid_left = fork();
	// error
	if (pid_left == 0)
	{
		dup2(pip[WRITE_END], STDOUT_FILENO); //error
		close(pip[READ_END]);
		close(pip[WRITE_END]);
		execute(node->left);
		exit(get_shell()->exit_status);
	}
	pid_right = fork();
	// error
	if (pid_right == 0)
	{
		dup2(pip[READ_END], STDIN_FILENO); //error
		close(pip[READ_END]);
		close(pip[WRITE_END]);
		execute(node->right);
		exit(get_shell()->exit_status);
	}
	close(pip[READ_END]);
	close(pip[WRITE_END]);
	waitpid(pid_left, &status_code, 0);
	if (WTERMSIG(status_code) == SIGPIPE)
		ft_putchar_fd('\n', 1);
	waitpid(pid_right, &status_code, 0);
	if (WTERMSIG(status_code) == SIGPIPE) //TODO: test exhaustively
		ft_putchar_fd('\n', 1);
	get_shell()->exit_status = WEXITSTATUS(status_code);
}

void	print_error(char *msg, char *file_name)
{
	printf("\e[31;1mError:\e[0m ");
	printf(msg, file_name);
	printf("\n");
}
