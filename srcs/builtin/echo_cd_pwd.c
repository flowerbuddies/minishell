/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/10 20:02:39 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	update_pwd_var(char *var_name);

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
	update_pwd_var("OLDPWD");
	if (chdir(path))
		action_failed("chdir");
	update_pwd_var("PWD");
	return (success);
}

static void	update_pwd_var(char *var_name)
{
	t_var	*pwd_var;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		action_failed("getcwd");
	pwd_var = vars_find(g_shell.vars, var_name);
	if (!pwd_var)
		vars_append(&g_shell.vars, vars_new(ft_strdup(var_name), cwd));
	else
	{
		free(pwd_var->value);
		pwd_var->value = cwd;
	}
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
