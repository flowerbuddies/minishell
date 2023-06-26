/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 17:39:24 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

static t_state	in_default_state_end(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '$' && tokenizer->line[i + 1] != ' '
		&& tokenizer->line[i + 1] != '\'' && tokenizer->line[i + 1] != '"'
		&& tokenizer->line[i + 1] != '\0')
		return (tokenizer->env_start_idx = i + 1, IN_ENV_VAR);
	else if (tokenizer->line[i] == '$')
		return (list_append(tokenizer, STRING, ft_strdup("$")), IN_DEFAULT);
	else if (tokenizer->line[i] != '<' && tokenizer->line[i] != '>')
		return (tokenizer->str_start_idx = i, IN_COMMAND);
	return (IN_DEFAULT);
}

t_state	in_default_state(t_tokenizer *tokenizer, int i)
{
	if (i > 0 && tokenizer->line[i] == '<' && tokenizer->line[i - 1] == '<')
		return (list_append(tokenizer, HEREDOC, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == '<' && tokenizer->line[i + 1] != '<')
		return (list_append(tokenizer, REDIR_IN, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == '>'
		&& i > 0 && tokenizer->line[i - 1] == '>')
		return (list_append(tokenizer, REDIR_OUT_APPEND, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == '>' && tokenizer->line[i + 1] != '>')
		return (list_append(tokenizer, REDIR_OUT, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == ' ')
		return (list_append(tokenizer, SPACE, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == '|')
		return (list_append(tokenizer, PIPE, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == '\'')
		return (tokenizer->str_start_idx = i + 1, IN_RAW_STRING);
	else if (tokenizer->line[i] == '"')
		return (tokenizer->str_start_idx = i + 1, IN_STRING);
	else if (tokenizer->line[i] == '$')
		return (list_append(tokenizer, STRING, ft_strdup("$")), IN_DEFAULT);
	else if (tokenizer->line[i + 1] == '\0')
		return (list_append(tokenizer, STRING,
				ft_substr(tokenizer->line, i, 1)), IN_DEFAULT);
	else
		return (in_default_state_end(tokenizer, i));
}
