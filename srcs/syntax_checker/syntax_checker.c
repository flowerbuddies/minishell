/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:27 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 19:20:25 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checker.h"
#include <stdio.h>

// in this context "special" refers to a pipe, a redirection or a heredoc

static void	print_error(char *msg, int idx, char *idx_msg)
{
	if (idx != -1)
		printf("%*c^——%s\n", idx + 11, ' ', idx_msg);
	printf("\e[31;1mSyntax Error:\e[0m %s\n", msg);
}

static bool	is_special(t_type type)
{
	return (type == PIPE || type == HEREDOC || type == REDIR_IN
		|| type == REDIR_OUT || type == REDIR_OUT_APPEND);
}

static bool	check_consecutive_special(t_tokenizer *tokenizer)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = tokenizer->tokens;
	while (current)
	{
		if (prev && is_special(prev->type) && is_special(current->type))
			if (!(prev->type == PIPE && current->type != PIPE))
				return (print_error("At least 2 consecutive special operators\
 (pipe/heredoc/redirectors)", -1, NULL), false);
		prev = current;
		current = current->next;
	}
	return (true);
}

static bool	check_ending_special(t_tokenizer *tokenizer)
{
	t_token	*current;

	current = tokenizer->tokens;
	while (current->next)
		current = current->next;
	if (is_special(current->type))
		return (print_error(
				"Ending with a special operator (pipe/heredoc/redirectors)",
				-1, NULL), false);
	return (true);
}

bool	check_syntax(t_tokenizer *tokenizer)
{
	if (tokenizer->str_start_idx != -1)
		return (print_error("Missing string termination",
				tokenizer->str_start_idx - 1, "start of the string"), false);
	if (tokenizer->tokens && tokenizer->tokens[0].type == PIPE)
		return (print_error("Invalid pipe location", 0, "here"), false);
	if (!check_consecutive_special(tokenizer))
		return (false);
	if (!check_ending_special(tokenizer))
		return (false);
	return (true);
}
