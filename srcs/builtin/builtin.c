/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/12 20:39:28 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"

bool	is_builtin(t_token *cmd)
{
	const char	*builtins[] = {
		"cd", "export", "unset", "echo", "pwd", "env", "exit", NULL};
	int			i;

	i = -1;
	while (builtins[++i])
		if (streq(builtins[i], cmd->data))
			return (true);
	return (false);
}

void	execute_builtin(t_token *cmd, bool is_parent)
{
	const char	*builtins[] = {
		"cd", "export", "unset", "echo", "pwd", "env", "exit", NULL};
	int			i;

	i = -1;
	while (builtins[++i])
	{
		if (streq(cmd->data, "echo") && !is_parent)
			return (echo(cmd->next));
		if (streq(cmd->data, "cd"))
			return (cd(cmd->next, is_parent));
		if (streq(cmd->data, "pwd") && !is_parent)
			return (pwd());
		if (streq(cmd->data, "export"))
			return (export(cmd->next, is_parent));
		if (streq(cmd->data, "unset"))
			return (unset(cmd->next));
		if (streq(cmd->data, "env") && !is_parent)
			return (env());
		if (streq(cmd->data, "exit") && is_parent)
			return (exit_builtin(cmd->next));
	}
}
