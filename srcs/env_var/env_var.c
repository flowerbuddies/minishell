/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:53:49 by mfm               #+#    #+#             */
/*   Updated: 2023/07/02 18:51:56 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	init_env_vars(char **ev)
{
	char	**splits;
	int		len;

	g_shell.raw_vars = ev;
	g_shell.vars = NULL;
	while (*ev)
	{
		splits = ft_split(*ev, '=');
		if (!splits)
			malloc_failed();
		len = 0;
		while (splits[len])
			len++;
		if (len == 1 || len == 2)
			vars_append(&g_shell.vars, vars_new(splits[0], splits[1]));
		else
			while (--len >= 0)
				free(splits[len]);
		free(splits);
		ev++;
	}
	vars_append(&g_shell.vars, vars_new(ft_strdup("?"), ft_strdup("0")));
}

void	set_last_exit_status(char *value)
{
	t_var	*var;

	var = vars_find(g_shell.vars, "?");
	free(var->value);
	var->value = value;
}
