/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:00:39 by mfm               #+#    #+#             */
/*   Updated: 2023/09/14 20:11:45 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var.h"
#include <stdlib.h>

t_var	*vars_new(char *name, char *value)
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

void	vars_append(t_var *var)
{
	t_var	*current;

	get_shell()->vars_len++;
	if (get_shell()->vars == NULL)
	{
		get_shell()->vars = var;
		return ;
	}
	current = get_shell()->vars;
	while (current->next)
		current = current->next;
	current->next = var;
	var->prev = current;
}

void	vars_delete_at(char *name)
{
	t_var	*current;

	current = vars_find(name);
	if (!current)
		return ;
	get_shell()->vars_len--; //TODO: useful, really?
	if (current->prev)
	{
		current->prev->next = current->next;
		if (current->next)
			current->next->prev = current->prev;
	}
	else
	{
		get_shell()->vars = current->next;
		current->prev = NULL;
	}
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
