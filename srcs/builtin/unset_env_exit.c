/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 19:14:51 by hunam            ###   ########.fr       */
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
	vars_delete_at(cmd->data);
}

void	env(void)
{
	g_shell.exit_status = success;
	vars_print(false);
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
			eprintf("\e[31;1mError:\e[0m numeric argument required\n", NULL, NULL);
			g_shell.exit_status = 255;
			return ;
		}
	}
	g_shell.exit_status = ft_atoi(cmd->data);
	if (!cmd->next)
		return ;
	eprintf("\e[31;1mError:\e[0m too many arguments\n", NULL, NULL);
	g_shell.exit_status = 1;
	g_shell.exit_needed = false;
}
