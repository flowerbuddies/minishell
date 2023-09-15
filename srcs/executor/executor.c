/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/09/15 16:21:14 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "libft.h"
#include "builtin.h"
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void	execute(t_node *ast)
{
	if (!ast)
		return ;
	if (ast->type == PIPE)
		return (execute_pipe(ast));
	return (execute_command(ast));
}

static void	set_command_exit_status(void)
{
	if (WIFSIGNALED(get_shell()->exit_status))
		get_shell()->exit_status = signal_base
		+ WTERMSIG(get_shell()->exit_status);
	else
		get_shell()->exit_status = WEXITSTATUS(get_shell()->exit_status);
}

void	execute_command(t_node *node)
{
	char		*path;
	const bool	is_a_builtin = is_builtin(node->token);
	pid_t		child;

	set_underscore_env_var(node->token);
	if (is_a_builtin)
		execute_builtin(node->token, true);
	child = fork();
	if (child == -1)
		action_failed("fork");
	if (child == 0)
	{
		if (!execute_redir(node->redirs))
			exit(get_shell()->exit_status);
		if (is_a_builtin)
			(execute_builtin(node->token, false),
				exit(get_shell()->exit_status));
		path = get_command_path(node->token->data);
		execve(path, get_argv(node->token), get_envp(get_shell()->vars));
		exit(get_shell()->exit_status);
	}
	waitpid(child, (int *)&get_shell()->exit_status, 0);
	set_command_exit_status();
}

static void	execute_side(t_node *node, int pip[2], pid_t pid, bool is_left)
{
	if (pid == -1)
		action_failed("fork");
	if (pid == 0)
	{
		if (is_left)
			dup2(pip[WRITE_END], STDOUT_FILENO);
		else
			dup2(pip[READ_END], STDIN_FILENO);
		close(pip[READ_END]);
		close(pip[WRITE_END]);
		if (is_left)
			execute(node->left);
		else
			execute(node->right);
		exit(get_shell()->exit_status);
	}
}

void	execute_pipe(t_node *node)
{
	int		pip[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_code;

	if (pipe(pip) == -1)
		action_failed("pipe");
	pid_left = fork();
	execute_side(node, pip, pid_left, true);
	pid_right = fork();
	execute_side(node, pip, pid_right, false);
	close(pip[READ_END]);
	close(pip[WRITE_END]);
	waitpid(pid_left, &status_code, 0);
	if (WTERMSIG(status_code) == SIGPIPE)
		ft_putchar_fd('\n', 1);
	waitpid(pid_right, &status_code, 0);
	if (WTERMSIG(status_code) == SIGPIPE)
		ft_putchar_fd('\n', 1);
	get_shell()->exit_status = WEXITSTATUS(status_code);
}
