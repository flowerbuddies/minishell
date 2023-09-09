/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/09/09 20:15:58 by hunam            ###   ########.fr       */
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
	if (ast->type == REDIR_OUT || ast->type == REDIR_OUT_APPEND)
		return (execute_redir_out(ast));
	if (ast->type == REDIR_IN || ast->type == HEREDOC)
		return (execute_redir_in(ast));
	return (execute_command(ast->token));
}

void	execute_command(t_token *cmd)
{
	int		status_code;
	t_child	child;

	child.cmd = cmd;
	child.path = get_command_path(cmd->data);
	if (!child.path)
		return ;
	if (fork() == 0)
	{
		// error
		if (execve(child.path, get_argv(child.cmd), get_envp(g_shell.vars))
			== -1)
			action_failed("execve");
	}
	wait(&status_code);
	// if (WIFSIGNALED(status_code))
	// 	return (signal_base + WTERMSIG(status_code));
	g_shell.exit_status = WEXITSTATUS(status_code);
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
		exit(g_shell.exit_status);
	}
	pid_right = fork();
	// error
	if (pid_right == 0)
	{
		dup2(pip[READ_END], STDIN_FILENO); //error
		close(pip[READ_END]);
		close(pip[WRITE_END]);
		execute(node->right);
		exit(g_shell.exit_status);
	}
	close(pip[READ_END]);
	close(pip[WRITE_END]);
	waitpid(pid_left, &status_code, 0);
	if (WTERMSIG(status_code) == SIGPIPE)
		ft_putchar_fd('\n', 1);
	waitpid(pid_right, &status_code, 0);
	if (WTERMSIG(status_code) == SIGPIPE)
		ft_putchar_fd('\n', 1);
	g_shell.exit_status = WEXITSTATUS(status_code);
}

void	print_error(char *msg, char *file_name)
{
	printf("\e[31;1mError:\e[0m ");
	printf(msg, file_name);
	printf("\n");
}
