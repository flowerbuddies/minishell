/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:29:00 by mfm               #+#    #+#             */
/*   Updated: 2023/06/29 16:33:58 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include "libft.h"

t_var	*get_var(t_var *vars, char *name)
{
	while (vars && ft_strncmp(vars->name, name, ft_strlen(name)))
		vars = vars->next;
	return (vars);
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
