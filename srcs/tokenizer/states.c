/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 22:00:31 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

t_state	state_default(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '<')
	{
		if (i > 0 && tokenizer->line[i - 1] == '<')
			list_append(tokenizer->tokens, HEREDOC, NULL);
		else if (tokenizer->line[i + 1] != '<')
			list_append(tokenizer->tokens, REDIR_IN, NULL);
	}
	else if (tokenizer->line[i] == '>')
	{
		if (i > 0 && tokenizer->line[i - 1] == '>')
			list_append(tokenizer->tokens, REDIR_OUT_APPEND, NULL);
		else if (tokenizer->line[i + 1] != '>')
			list_append(tokenizer->tokens, REDIR_OUT, NULL);
	}
	else if (tokenizer->line[i] == ' ')
		return (list_append(tokenizer->tokens, SPACE, NULL), DEFAULT);
	else if (tokenizer->line[i] == '|')
		list_append(tokenizer->tokens, PIPE, NULL);
	else if (tokenizer->line[i] == '\'')
		return (tokenizer->str_start_idx = i + 1, IN_RAW_STRING);
	else if (tokenizer->line[i] == '"')
		return (tokenizer->str_start_idx = i + 1, IN_STRING);
	else if (tokenizer->line[i] == '$')
		return (tokenizer->env_start_idx = i + 1, IN_ENV_VAR);
	else
		return (tokenizer->str_start_idx = i, IN_COMMAND);
	return (DEFAULT);
}

t_state	in_command_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == ' ')
	{
		list_append(tokenizer->tokens, COMMAND, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (DEFAULT);
	}
	return (IN_COMMAND);
}

t_state	in_raw_string_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer->tokens, RAW_STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (DEFAULT);
	}
	return (IN_RAW_STRING);
}

t_state	in_string_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '"')
	{
		list_append(tokenizer->tokens, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (DEFAULT);
	}
	else if (tokenizer->line[i] == '$')
	{
		list_append(tokenizer->tokens, STRING,
			ft_substr(tokenizer->line, tokenizer->str_start_idx,
				i - tokenizer->str_start_idx));
		tokenizer->env_start_idx = i + 1;
		return (IN_ENV_VAR);
	}
	return (IN_STRING);
}

t_state	in_env_var_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == ' ')
	{
		list_append(tokenizer->tokens, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		list_append(tokenizer->tokens, SPACE, NULL);
		if (tokenizer->str_start_idx == -1)
			return (DEFAULT);
		else
			return (tokenizer->str_start_idx = i + 1, IN_STRING);
	}
	if (tokenizer->line[i] == '"')
	{
		list_append(tokenizer->tokens, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		return (tokenizer->str_start_idx = i, IN_STRING);
	}
	if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer->tokens, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		return (tokenizer->str_start_idx = i, IN_RAW_STRING);
	}
	return (IN_ENV_VAR);
}
