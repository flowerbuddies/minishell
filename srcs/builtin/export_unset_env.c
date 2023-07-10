/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 18:40:15 by hunam            ###   ########.fr       */
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

void	export(t_token *cmd)
{
	char	**parts;
	int		parts_len;

	if (!cmd)
		return (write(1, "\e[31;1mError:\e[0m missing an argument\n", 38),
			g_shell.exit_status = invalid_usage, free(NULL));
	if (!ft_strchr(cmd->data, '='))
		return ;
	parts = ft_split(cmd->data, '=');
	if (!parts)
		action_failed("ft_split");
	parts_len = array_len(parts);
	if (parts_len != 1 && parts_len != 2)
		return (write(1, "\e[31;1mError:\e[0m incorrect usage\n", 34),
			g_shell.exit_status = invalid_usage, free(NULL)); //TODO: maybe support environment variables with an equal sign
	if (vars_find(g_shell.vars, parts[0]))
		vars_delete_at(g_shell.vars, parts[0]);
	if (parts_len == 1)
		vars_append(&g_shell.vars, vars_new(parts[0], ft_strdup("")));
	else
		vars_append(&g_shell.vars, vars_new(parts[0], parts[1]));
	free(parts);
}

void	unset(t_token *cmd)
{
	if (!cmd)
		return ;
	vars_delete_at(g_shell.vars, cmd->data);
}

void	env(t_token *cmd)
{
	if (cmd)
	{
		write(1, "\e[31;1mError:\e[0m too many arguments\n", 37);
		g_shell.exit_status = invalid_usage;
		return ;
	}
	vars_print(g_shell.vars);
}
