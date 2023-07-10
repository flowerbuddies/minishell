/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 19:40:06 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	echo(t_token *cmd)
{
	bool	trailing_nl;
	bool	is_first;

	trailing_nl = true;
	if (cmd && streq(cmd->data, "-n"))
	{
		trailing_nl = false;
		cmd = cmd->next;
	}
	is_first = true;
	while (cmd)
	{
		if (is_first)
			is_first = false;
		else
			write(1, " ", 1);
		write(1, cmd->data, ft_strlen(cmd->data));
		cmd = cmd->next;
	}
	if (trailing_nl)
		write(1, "\n", 1);
	return (success);
}

int	cd(t_token *cmd)
{
	char	*path;
	t_var	*home_var;

	if (cmd)
		path = cmd->data;
	else
	{
		home_var = vars_find(g_shell.vars, "HOME");
		if (!home_var)
			return (write(1, "\e[31;1mError:\e[0m $HOME not set\n", 32), failure);
		path = home_var->value;
	}
	chdir(path);
	return (success);
}

int	pwd(void)
{
	const char	*cwd = getcwd(NULL, 0);

	if (!cwd)
		action_failed("getcwd");
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free((char *)cwd);
	return (success);
}
