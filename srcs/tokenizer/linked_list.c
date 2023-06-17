/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 15:02:03 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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

void	list_print(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == SPACE)
			printf("sp ");
		else if (tokens->type == COMMAND)
			printf("cmd ");
		else if (tokens->type == ENV_VAR)
			printf("$%s ", tokens->data);
		else if (tokens->type == RAW_STRING)
			printf("'%s' ", tokens->data);
		else if (tokens->type == STRING)
			printf("\"%s\" ", tokens->data);
		else if (tokens->type == REDIR_IN)
			printf("< ");
		else if (tokens->type == REDIR_OUT)
			printf("> ");
		else if (tokens->type == HEREDOC)
			printf("<< ");
		else if (tokens->type == REDIR_OUT_APPEND)
			printf(">> ");
		else if (tokens->type == PIPE)
			printf("| ");
		tokens = tokens->next;
	}
	printf("\n");
}
