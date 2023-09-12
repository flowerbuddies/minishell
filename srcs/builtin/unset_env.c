/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/12 18:58:10 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	unset(t_token *cmd)
{
	if (!cmd)
		return ;
	vars_delete_at(g_shell.vars, cmd->data);
}

void	env(void)
{
	vars_print(g_shell.vars, false);
}
