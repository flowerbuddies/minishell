/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_env_vars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:59:58 by mfm               #+#    #+#             */
/*   Updated: 2023/09/13 19:02:04 by marmulle         ###   ########.fr       */
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
			if (current->data[0] == '?' && current->data[1] == '\0')
			{
				free(current->data);
				current->data = ft_itoa(g_shell.exit_status);
			}
			else
			{
				var = vars_find(current->data);
				free(current->data);
				if (var)
					current->data = ft_strdup(var->value);
				else
					current->data = ft_strdup("");
			}
		}
		current = current->next;
	}
}
