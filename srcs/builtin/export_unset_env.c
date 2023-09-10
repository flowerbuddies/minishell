/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/10 19:24:26 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	export(t_token *cmd)
{
	char	**parts;
	int		parts_len;

	if (!cmd)
		return (write(1, "\e[31;1mError:\e[0m missing an argument\n", 38),
			invalid_usage);
	if (!ft_strchr(cmd->data, '='))
		return (success);
	parts = ft_split(cmd->data, '=');
	if (!parts)
		action_failed("ft_split");
	parts_len = array_len(parts);
	if (parts_len != 1 && parts_len != 2)
		return (write(1, "\e[31;1mError:\e[0m incorrect usage\n", 34),
			invalid_usage); //TODO: maybe support environment variables with an equal sign
	if (vars_find(g_shell.vars, parts[0]))
		vars_delete_at(g_shell.vars, parts[0]);
	if (parts_len == 1)
		vars_append(&g_shell.vars, vars_new(parts[0], ft_strdup("")));
	else
		vars_append(&g_shell.vars, vars_new(parts[0], parts[1]));
	free(parts);
	return (success);
}

int	unset(t_token *cmd)
{
	if (!cmd)
		return (success);
	vars_delete_at(g_shell.vars, cmd->data);
	return (success);
}

int	env(t_token *cmd)
{
	if (cmd)
		return (write(1, "\e[31;1mError:\e[0m too many arguments\n", 37),
			invalid_usage);
	vars_print(g_shell.vars);
	return (success);
}
