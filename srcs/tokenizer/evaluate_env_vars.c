/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:59:58 by mfm               #+#    #+#             */
/*   Updated: 2023/06/29 19:18:42 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include <stdlib.h>

void	evaluate_env_vars(t_tokenizer *tokenizer)
{
	t_token	*current;
	char	*value;

	current = tokenizer->tokens;
	while (current)
	{
		if (current->type == ENV_VAR && current->data)
		{
			current->type = STRING;
			value = get_var(g_shell.vars, current->data)->value;
			free(current->data);
			current->data = value;
		}
		current = current->next;
	}
}
