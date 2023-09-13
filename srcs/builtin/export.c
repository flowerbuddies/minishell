/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/12 20:38:24 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static bool	is_valid_identifier(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

void	export(t_token *cmd, bool is_parent)
{
	char	**parts;
	int		parts_len;

	g_shell.exit_status = success;
	if (!cmd)
	{
		if (!is_parent)
			vars_print(g_shell.vars, true);
		return ;
	}
	if (!ft_strchr(cmd->data, '='))
		return ;
	parts = ft_split(cmd->data, '=');
	if (!parts)
		return ((void)(g_shell.exit_status = failure));
	parts_len = len2d(parts);
	if (parts_len != 1 && parts_len != 2) //TODO(mark): fix export 5f
	{
		g_shell.exit_status = failure;
		return (free2d(parts));
	}
	if (!is_valid_identifier(parts[0]))
	{
		if (!is_parent)
			ft_putstr_fd("\e[31;1mError:\e[0m invalid identifier\n", 2);
		g_shell.exit_status = failure;
		return (free2d(parts));
	}
	if (!is_parent)
		return (free2d(parts));
	if (vars_find(g_shell.vars, parts[0]))
		vars_delete_at(g_shell.vars, parts[0]);
	if (parts_len == 1)
		vars_append(&g_shell.vars, vars_new(parts[0], ft_strdup("")));
	else
		vars_append(&g_shell.vars, vars_new(parts[0], parts[1]));
	free(parts);
}