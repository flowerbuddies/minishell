/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_setter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:21 by marmulle          #+#    #+#             */
/*   Updated: 2023/06/22 16:16:03 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

t_token	*list_new(t_tokenizer *tokenizer)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	if (!out)
	{
		tokenizer->errored = true;
		return (NULL);
	}
	out->type = _NOT_SET;
	out->data = NULL;
	out->next = NULL;
	return (out);
}

void	list_append(t_tokenizer *tokenizer, t_type type, char *data)
{
	t_token	*current;

	current = tokenizer->tokens;
	if (current->type == _NOT_SET)
	{
		current->type = type;
		current->data = data;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = list_new(tokenizer);
	if (tokenizer->errored)
		return ;
	current->next->type = type;
	current->next->data = data;
	current->next->next = NULL;
}

void	list_delete_at(t_token *tokens, int idx)
{
	t_token	*current;

	current = list_at(tokens, idx);
	if (current->data)
		free(current->data);
	if (current->next)
	{
		current->type = current->next->type;
		current->next = current->next->next;
	}
	else
	{
		current->type = _NOT_SET;
		current->next = NULL;
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
