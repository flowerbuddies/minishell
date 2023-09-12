/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/12 20:39:25 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	unset(t_token *cmd)
{
	g_shell.exit_status = success;
	if (!cmd)
		return ;
	vars_delete_at(g_shell.vars, cmd->data);
}

void	env(void)
{
	g_shell.exit_status = success;
	vars_print(g_shell.vars, false);
}

void	exit_builtin(t_token *cmd)
{
	int	i;

	g_shell.exit_needed = true;
	if (!cmd)
		return ;
	i = -1;
	while (cmd->data[++i])
	{
		if (!ft_isdigit(cmd->data[i]))
		{
			ft_putstr_fd("\e[31;1mError:\e[0m numeric argument required\n", 2);
			g_shell.exit_status = 255;
			return ;
		}
	}
	g_shell.exit_status = ft_atoi(cmd->data);
	if (!cmd->next)
		return ;
	ft_putstr_fd("\e[31;1mError:\e[0m too many arguments\n", 2);
	g_shell.exit_status = 1;
	g_shell.exit_needed = false;
}
