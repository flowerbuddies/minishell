/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:59:58 by mfm               #+#    #+#             */
/*   Updated: 2023/07/01 16:18:54 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

void	evaluate_env_vars(t_tokenizer *tokenizer)
{
	t_token	*current;
	t_var	*var;

	current = tokenizer->tokens;
	while (current)
	{
		if (current->type == ENV_VAR)
		{
			current->type = STRING;
			var = vars_find(g_shell.vars, current->data);
			free(current->data);
			if (var)
				current->data = ft_strdup(var->value);
			else
				current->data = ft_strdup("");
		}
		current = current->next;
	}
}
