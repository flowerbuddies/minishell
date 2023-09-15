/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/15 15:23:02 by marmulle         ###   ########.fr       */
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

static bool	check_parts(char **parts, int parts_len, bool is_parent)
{
	if (parts_len != 1 && parts_len != 2)
	{
		get_shell()->exit_status = failure;
		return (true);
	}
	if (!is_valid_identifier(parts[0]))
	{
		if (!is_parent)
			eprintf("\e[31;1mError:\e[0m invalid identifier\n", NULL, NULL);
		get_shell()->exit_status = failure;
		return (true);
	}
	return (false);
}

static void	handle_export_cmd(t_token *cmd, bool is_parent)
{
	char	**parts;
	int		parts_len;

	if (!ft_strchr(cmd->data, '='))
		return ;
	parts = ft_split(cmd->data, '=');
	if (!parts)
		return ((void)(get_shell()->exit_status = failure));
	parts_len = len2d(parts);
	if (check_parts(parts, parts_len, is_parent))
		return (free2d(parts));
	if (!is_parent)
		return (free2d(parts));
	if (vars_find(parts[0]))
		vars_delete_at(parts[0]);
	if (parts_len == 1)
		vars_append(vars_new(parts[0], ft_strdup("")));
	else
		vars_append(vars_new(parts[0], parts[1]));
	free(parts);
	cmd = cmd->next;
}

void	export(t_token *cmd, bool is_parent)
{
	get_shell()->exit_status = success;
	if (!cmd)
	{
		if (!is_parent)
			vars_print(true);
		return ;
	}
	while (cmd)
	{
		handle_export_cmd(cmd, is_parent);
		cmd = cmd->next;
	}
}
