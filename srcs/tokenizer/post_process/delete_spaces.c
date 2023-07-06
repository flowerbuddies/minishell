/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:45:22 by mfm               #+#    #+#             */
/*   Updated: 2023/07/04 23:40:42 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	delete_leading_spaces(t_tokenizer *tokenizer)
{
	t_token	*current;
	int		num_to_del;

	current = tokenizer->tokens;
	num_to_del = 0;
	while (current && current->type == SPC)
	{
		current = current->next;
		num_to_del++;
	}
	while (num_to_del--)
		tokens_delete_at(tokenizer, 0);
	tokenizer->tokens = current;
}

void	delete_space_tokens(t_tokenizer *tokenizer)
{
	t_token	*current;
	int		i;

	delete_leading_spaces(tokenizer);
	current = tokenizer->tokens;
	if (!current)
		return ;
	i = 0;
	while (current->next)
	{
		if (current->next->type == SPC)
			tokens_delete_at(tokenizer, i + 1);
		else
		{
			current = current->next;
			i++;
		}
	}
}
