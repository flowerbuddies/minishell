/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:21:24 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/04 23:40:42 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokenizer.h"

t_token	*tokens_at(t_token *tokens, int idx)
{
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
