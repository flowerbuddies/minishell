/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 13:25:46 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*list_new(void)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	out->next = NULL;
	out->type = UNSET;
	return (out);
}

bool	list_append(t_token *tokens, t_type type, char *data)
{
	if (tokens->type == UNSET)
	{
		tokens->type = type;
		tokens->data = data;
		return (true);
	}
	while (tokens->next)
		tokens = tokens->next;
	tokens->next = list_new();
	if (!tokens->next)
		return (false);
	tokens->next->type = type;
	tokens->next->data = data;
	tokens->next->next = NULL;
	return (true);
}

t_token	*list_at(t_token *tokens, int idx)
{
	while (idx--)
		tokens = tokens->next;
	return (tokens);
}

void	list_free(t_token *tokens)
{
	if (tokens->next)
		list_free(tokens->next);
	if (tokens->data)
		free(tokens->data);
	free(tokens);
}
