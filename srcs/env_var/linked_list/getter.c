/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:29:00 by mfm               #+#    #+#             */
/*   Updated: 2023/07/10 18:19:35 by hunam            ###   ########.fr       */
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

void	vars_print(t_var *vars)
{
	while (vars)
	{
		ft_printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
}
