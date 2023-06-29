/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:53:49 by mfm               #+#    #+#             */
/*   Updated: 2023/06/27 20:38:59 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

bool	init_env_vars(char **ev)
{
	char	**splits;
	int		len;

	g_shell.vars = NULL;
	while (*ev)
	{
		splits = ft_split(*ev, '=');
		if (!splits)
			return (false);
		len = 0;
		while (splits[len])
			len++;
		if (len == 1 || len == 2)
			vars_append(&g_shell.vars, new_var(splits[0], splits[1]));
		ev++;
	}
	return (true);
}
