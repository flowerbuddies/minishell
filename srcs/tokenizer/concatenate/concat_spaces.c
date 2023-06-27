/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 17:45:22 by mfm               #+#    #+#             */
/*   Updated: 2023/06/26 18:34:04 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdlib.h>

static void	free_space_reattach(t_token *first_space, t_token *attach)
{
	t_token	*current;
	t_token	*hold;

	current = first_space->next;
	while(current && current->type == SPACE)
	{
		hold = current->next;
		free(current);
		current = hold;
	}
	first_space->next = attach;
}

void	concat_space_tokens(t_tokenizer *tokenizer)
{
	t_token	*current;
	t_token	*current_space;
	t_token	*first_space;

	current = tokenizer->tokens;
	while(current)
	{
		if (current->type == SPACE)
		{
			first_space = current;
			current_space = current;
			while (current_space->next && current_space->next->type == SPACE)
				current_space = current_space->next;
			if (first_space != current_space)
				free_space_reattach(first_space, current_space->next);
		}
		current = current->next;
	}
}
