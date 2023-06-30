/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:00:39 by mfm               #+#    #+#             */
/*   Updated: 2023/06/30 23:39:40 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_var.h"
#include <stdlib.h>

t_var	*new_var(char *name, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	var->next = NULL;
	var->prev = NULL;
	return (var);
}

void	vars_append(t_var **vars, t_var *var)
{
	t_var	*current;

	if (*vars == NULL)
	{
		*vars = var;
		return ;
	}
	current = *vars;
	while (current->next)
		current = current->next;
	current->next = var;
	var->prev = current;
}

void	vars_delete_at(t_var *vars, char *name)
{
	t_var	*previous;
	t_var	*current;

	current = get_var(vars, name);
	if (!current)
		return ;
	previous = current->prev;
	previous->next = current->next;
	if (current->name)
		free(current->name);
	if (current->value)
		free(current->value);
	free(current);
}

void	vars_free(t_var *var)
{
	if (var->next)
		vars_free(var->next);
	free(var->name);
	free(var->value);
	free(var);
}
