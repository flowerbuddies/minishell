/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:29:00 by mfm               #+#    #+#             */
/*   Updated: 2023/09/12 17:29:17 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
#include "libft.h"

t_var	*vars_find(t_var *vars, char *name)
{
	while (vars)
	{
		if (streq(vars->name, name))
			return (vars);
		vars = vars->next;
	}
	return (NULL);
}

void	vars_print(t_var *vars, bool prepend_declare)
{
	while (vars)
	{
		if (prepend_declare)
			ft_printf("declare -x ");
		ft_printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
}
