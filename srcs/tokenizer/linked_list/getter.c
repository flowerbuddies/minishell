/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:24 by marmulle          #+#    #+#             */
/*   Updated: 2023/09/15 16:14:44 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include <stdio.h>

t_token	*tokens_at(t_token *tokens, int idx)
{
	if (idx < 0)
		return (NULL);
	while (idx--)
		tokens = tokens->next;
	return (tokens);
}

void	tokens_print(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == SPC)
			printf("sp ");
		else if (tokens->type == ENV_VAR)
			printf("$%s ", tokens->data);
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
