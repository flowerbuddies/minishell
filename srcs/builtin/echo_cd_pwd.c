/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/13 14:56:26 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static void	update_pwd_var(char *var_name);

void	echo(t_token *cmd)
{
	bool	trailing_nl;
	bool	is_first;

	g_shell.exit_status = success;
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
}

void	cd(t_token *cmd, bool is_parent)
{
	char	*path;
	t_var	*home_var;

	g_shell.exit_status = success;
	if (cmd)
		path = cmd->data;
	else
	{
		home_var = vars_find(g_shell.vars, "HOME");
		if (!home_var)
		{
			g_shell.exit_status = failure;
			if (!is_parent)
				ft_putstr_fd("\e[31;1mError:\e[0m $HOME not set\n", 2);
			return ;
		}
		path = home_var->value;
	}
	update_pwd_var("OLDPWD");
	if (is_parent && chdir(path))
	{
		g_shell.exit_status = failure;
		ft_putstr_fd("\e[31;1mError:\e[0m No such file or directory\n", 2);
		return ;
	}
	update_pwd_var("PWD");
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

void	pwd(void)
{
	const char	*cwd = getcwd(NULL, 0);

	g_shell.exit_status = success;
	if (!cwd)
		action_failed("getcwd");
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	free((char *)cwd);
}
