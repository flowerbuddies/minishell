/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/23 16:10:24 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

t_state	default_state(t_tokenizer *tokenizer, int i)
{
	if (i > 0 && tokenizer->line[i] == '<'
		&& tokenizer->line[i - 1] == '<')
		list_append(tokenizer, HEREDOC, NULL);
	else if (tokenizer->line[i] == '<' && tokenizer->line[i + 1] != '<')
		list_append(tokenizer, REDIR_IN, NULL);
	else if (tokenizer->line[i] == '>'
		&& i > 0 && tokenizer->line[i - 1] == '>')
		list_append(tokenizer, REDIR_OUT_APPEND, NULL);
	else if (tokenizer->line[i] == '>' && tokenizer->line[i + 1] != '>')
		list_append(tokenizer, REDIR_OUT, NULL);
	else if (tokenizer->line[i] == ' ')
		return (list_append(tokenizer, SPACE, NULL), IN_DEFAULT);
	else if (tokenizer->line[i] == '|')
		list_append(tokenizer, PIPE, NULL);
	else if (tokenizer->line[i] == '\'')
		return (tokenizer->str_start_idx = i + 1, IN_RAW_STRING);
	else if (tokenizer->line[i] == '"')
		return (tokenizer->str_start_idx = i + 1, IN_STRING);
	else if (tokenizer->line[i] == '$')
		return (list_append(tokenizer, STRING, ft_strdup("$")), IN_DEFAULT);
	else if (tokenizer->line[i + 1] == '\0')
		return (list_append(tokenizer, STRING,
				ft_substr(tokenizer->line, i, 1)), IN_DEFAULT);
	else if (tokenizer->line[i] != '<' && tokenizer->line[i] != '>')
		return (tokenizer->str_start_idx = i, IN_COMMAND);
	return (IN_DEFAULT);
}

t_state	in_command_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == ' ')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		list_append(tokenizer, SPACE, NULL);
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	else if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = i + 1;
		return (IN_RAW_STRING);
	}
	else if (tokenizer->line[i] == '"')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = i + 1;
		return (IN_STRING);
	}
	if (tokenizer->line[i + 1] == '\0')
	{
		ft_printf("HEY?????\n");
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx + 1));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	return (IN_COMMAND);
}

t_state	in_raw_string_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	return (IN_RAW_STRING);
}

t_state	in_string_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '"')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	else if (tokenizer->line[i] == '$')
	{
		list_append(tokenizer, STRING,
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
		list_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		if (tokenizer->str_start_idx == -1)
			return (list_append(tokenizer, SPACE, NULL), IN_DEFAULT);
		else
			return (tokenizer->str_start_idx = i, IN_STRING);
	}
	else if (tokenizer->line[i] == '"')
	{
		list_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		if (tokenizer->str_start_idx == -1)
			return (tokenizer->str_start_idx = i, IN_STRING);
		else
			return (IN_DEFAULT);
	}
	if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		return (tokenizer->str_start_idx = i, IN_RAW_STRING);
	}
	if (tokenizer->line[i + 1] == '\0')
	{
		list_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx + 1));
		return (IN_DEFAULT);
	}
	return (IN_ENV_VAR);
}
