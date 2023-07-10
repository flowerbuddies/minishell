/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 19:44:02 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"

bool	is_builtin(const char *cmd)
{
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int			i;

	i = -1;
	while (builtins[++i])
		if (streq(builtins[i], cmd))
			return (true);
	return (false);
}

int	execute_builtin(t_token *cmd)
{
	if (streq(cmd->data, "echo"))
		return (echo(cmd->next));
	if (streq(cmd->data, "cd"))
		return (cd(cmd->next));
	if (streq(cmd->data, "pwd"))
		return (pwd());
	if (streq(cmd->data, "export"))
		return (export(cmd->next));
	if (streq(cmd->data, "unset"))
		return (unset(cmd->next));
	if (streq(cmd->data, "env"))
		return (env(cmd->next));
	return (g_shell.exit_status);
}
