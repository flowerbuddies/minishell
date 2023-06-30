/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:21 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/01 01:32:38 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

t_token	*tokens_new(t_tokenizer *tokenizer)
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

void	tokens_append(t_tokenizer *tokenizer, t_type type, char *data)
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
	current->next = tokens_new(tokenizer);
	if (tokenizer->errored)
		return ;
	current->next->type = type;
	current->next->data = data;
	current->next->next = NULL;
}

// Will intentionally segfault when trying to access illegal token
void	tokens_delete_at(t_tokenizer *tokenizer, int idx)
{
	t_token	*current;
	t_token	*previous;

	if (idx == 0)
	{
		current = tokenizer->tokens->next;
		if (tokenizer->tokens->data)
			free(tokenizer->tokens->data);
		free(tokenizer->tokens);
		tokenizer->tokens = current;
		return ;
	}
	previous = tokens_at(tokenizer->tokens, idx - 1);
	current = previous->next;
	if (current->data)
		free(current->data);
	previous->next = current->next;
	free(current);
}

void	tokens_free(t_token *tokens)
{
	if (!tokens)
		return ;
	if (tokens->next)
		tokens_free(tokens->next);
	if (tokens->data)
		free(tokens->data);
	free(tokens);
}
