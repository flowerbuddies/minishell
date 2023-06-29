/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:21 by marmulle          #+#    #+#             */
/*   Updated: 2023/06/27 18:27:29 by mfm              ###   ########.fr       */
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

void	list_free(t_token *tokens)
{
	if (tokens->next)
		list_free(tokens->next);
	if (tokens->data)
		free(tokens->data);
	free(tokens);
}
