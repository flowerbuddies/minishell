/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 20:11:45 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static void	update_pwd_var(char *var_name);

void	echo(t_token *cmd)
{
	bool	trailing_nl;
	bool	is_first;

	get_shell()->exit_status = success;
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
			printf(" ");
		printf("%s", cmd->data);
		cmd = cmd->next;
	}
	if (trailing_nl)
		printf("\n");
}

void	cd(t_token *cmd, bool is_parent)
{
	char	*path;
	t_var	*home_var;

	get_shell()->exit_status = success;
	if (cmd)
		path = cmd->data;
	else
	{
		home_var = vars_find("HOME");
		if (!home_var)
		{
			get_shell()->exit_status = failure;
			if (!is_parent)
				eprintf("\e[31;1mError:\e[0m $HOME not set\n", NULL, NULL);
			return ;
		}
		path = home_var->value;
	}
	update_pwd_var("OLDPWD");
	if (chdir(path))
	{
		get_shell()->exit_status = failure;
		if (is_parent)
			eprintf("\e[31;1mError:\e[0m No such file or directory\n", NULL, NULL);
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
	pwd_var = vars_find(var_name);
	if (!pwd_var)
		vars_append(vars_new(ft_strdup(var_name), cwd));
	else
	{
		free(pwd_var->value);
		pwd_var->value = cwd;
	}
}

void	pwd(void)
{
	const char	*cwd = getcwd(NULL, 0);

	get_shell()->exit_status = success;
	if (!cwd)
		action_failed("getcwd");
	printf("%s\n", cwd);
	free((char *)cwd);
}
