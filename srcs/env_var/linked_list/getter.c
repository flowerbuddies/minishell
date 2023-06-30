/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:29:00 by mfm               #+#    #+#             */
/*   Updated: 2023/07/01 01:38:26 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
#include "libft.h"

t_var	*vars_at(t_var *vars, char *name)
{
	while (vars)
	{
		if (ft_strlen(vars->name) == ft_strlen(name)
			&& ft_strncmp(vars->name, name, ft_strlen(name)) == 0)
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
