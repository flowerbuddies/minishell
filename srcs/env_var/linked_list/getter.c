/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:29:00 by mfm               #+#    #+#             */
/*   Updated: 2023/06/29 22:39:09 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
#include "libft.h"

t_var	*get_var(t_var *vars, char *name)
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

void	print_var(t_var *var)
{
	ft_printf("%s=%s\n", var->name, var->value);
}

void	print_vars(t_var *vars)
{
	while (vars)
	{
		print_var(vars);
		vars = vars->next;
	}
}
