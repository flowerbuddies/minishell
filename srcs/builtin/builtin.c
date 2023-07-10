/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 18:05:51 by hunam            ###   ########.fr       */
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

void	execute_builtin(t_token *cmd)
{
	if (streq(cmd->data, "echo"))
		echo(cmd->next);
	else if (streq(cmd->data, "cd"))
		cd(cmd->next);
	else if (streq(cmd->data, "pwd"))
		pwd();
	else if (streq(cmd->data, "export"))
		export(cmd->next);
	else if (streq(cmd->data, "unset"))
		unset(cmd->next);
	else if (streq(cmd->data, "env"))
		env(cmd->next);
}
