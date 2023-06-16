/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/16 02:32:12 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*new_list(void)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	out->next = NULL;
	out->type = UNSET;
	return (out);
}

bool	append(t_token *tokens, t_type type, char *data)
{
	if (tokens->type == UNSET)
	{
		tokens->type = type;
		tokens->data = data;
		return (true);
	}
	while (tokens->next)
		tokens = tokens->next;
	tokens->next = new_list();
	if (!tokens->next)
		return (false);
	tokens->next->type = type;
	tokens->next->data = data;
	tokens->next->next = NULL;
	return (true);
}

t_token	*get(t_token *tokens, int idx)
{
	while (idx--)
		tokens = tokens->next;
	return (tokens);
}

void	free_list(t_token *tokens)
{
	if (tokens->next)
		free_list(tokens->next);
	if (tokens->data)
		free(tokens->data);
	free(tokens);
}
