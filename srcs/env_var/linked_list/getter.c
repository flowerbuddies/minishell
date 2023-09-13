/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:29:00 by mfm               #+#    #+#             */
/*   Updated: 2023/09/13 19:00:49 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
#include "libft.h"

t_var	*vars_find(char *name)
{
	t_var	*current;

	current = g_shell.vars;
	while (current)
	{
		if (streq(current->name, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	vars_print(bool prepend_declare)
{
	t_var	*current;

	current = g_shell.vars;
	while (current)
	{
		if (prepend_declare)
			ft_printf("declare -x ");
		ft_printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
