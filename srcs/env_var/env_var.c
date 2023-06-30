/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:53:49 by mfm               #+#    #+#             */
/*   Updated: 2023/07/01 01:40:17 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	init_env_vars(char **ev)
{
	char	**splits;
	int		len;

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
}
