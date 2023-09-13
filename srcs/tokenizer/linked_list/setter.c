/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:21 by marmulle          #+#    #+#             */
/*   Updated: 2023/09/13 16:10:03 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "minishell.h"

t_token	*tokens_new(void)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	if (!out)
		action_failed("tokens_new");
	out->type = _NOT_SET;
	out->gate = false;
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
	current->next = tokens_new();
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
