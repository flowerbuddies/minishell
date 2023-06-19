/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_setter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:21 by marmulle          #+#    #+#             */
/*   Updated: 2023/06/19 19:27:27 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

t_token	*list_new(void)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	out->next = NULL;
	out->type = _NOT_SET;
	return (out);
}

bool	list_append(t_token *tokens, t_type type, char *data)
{
	if (tokens->type == _NOT_SET)
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

void	list_delete_at(t_token *tokens, int idx)
{
	t_token	*link;

	link = list_at(tokens, idx);
	if (link->data)
		free(link->data);
	if (link->next)
	{
		link->type = link->next->type;
		link->next = link->next->next;
	}
	else
	{
		link->type = _NOT_SET;
		link->next = NULL;
	}
}

void	list_free(t_token *tokens)
{
	if (tokens->next)
		list_free(tokens->next);
	if (tokens->data)
		free(tokens->data);
	free(tokens);
}
