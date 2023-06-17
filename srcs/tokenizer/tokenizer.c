/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 17:41:18 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "libft.h"

//TODO: think about merging COMMAND, RAW_STRING and STRING as we already get the env vars at this stage, they all just become strings

t_token	*tokenize(const char *line)
{
	t_token		*tokens;
	int			i;
	t_state		state;
	int			str_start_idx;
	int			env_start_idx;

	tokens = list_new();
	i = -1;
	state = DEFAULT;
	str_start_idx = -1;
	while (line[++i])
	{
		if (state == DEFAULT)
		{
			if (line[i] == ' ')
				list_append(tokens, SPACE, NULL);
			else if (line[i] == '<')
			{
				if (i > 0 && line[i - 1] == '<')
					list_append(tokens, HEREDOC, NULL);
				else if (line[i + 1] == '<')
					continue ;
				else
					list_append(tokens, REDIR_IN, NULL);
			}
			else if (line[i] == '>')
			{
				if (i > 0 && line[i - 1] == '>')
					list_append(tokens, REDIR_OUT_APPEND, NULL);
				else if (line[i + 1] == '>')
					continue ;
				else
					list_append(tokens, REDIR_OUT, NULL);
			}
			else if (line[i] == '|')
				list_append(tokens, PIPE, NULL);
			else if (line[i] == '\'')
			{
				str_start_idx = i + 1;
				state = IN_RAW_STRING;
			}
			else if (line[i] == '"')
			{
				str_start_idx = i + 1;
				state = IN_STRING;
			}
			else if (line[i] == '$')
			{
				env_start_idx = i + 1;
				state = IN_ENV_VAR;
			}
			else
			{
				str_start_idx = i;
				state = IN_COMMAND;
			}
		}
		else if (state == IN_COMMAND)
		{
			if (line[i] == ' ')
			{
				list_append(tokens, COMMAND, ft_substr(line, str_start_idx, i - str_start_idx));
				str_start_idx = -1;
				state = DEFAULT;
			}
		}
		else if (state == IN_RAW_STRING)
		{
			if (line[i] == '\'')
			{
				list_append(tokens, RAW_STRING, ft_substr(line, str_start_idx, i - str_start_idx));
				str_start_idx = -1;
				state = DEFAULT;
			}
		}
		else if (state == IN_STRING)
		{
			if (line[i] == '"')
			{
				list_append(tokens, STRING, ft_substr(line, str_start_idx, i - str_start_idx));
				str_start_idx = -1;
				state = DEFAULT;
			}
			else if (line[i] == '$')
			{
				list_append(tokens, STRING, ft_substr(line, str_start_idx, i - str_start_idx));
				env_start_idx = i + 1;
				state = IN_ENV_VAR;
			}
		}
		else if (state == IN_ENV_VAR)
		{
			if (line[i] == ' ')
			{
				list_append(tokens, ENV_VAR, ft_substr(line, env_start_idx, i - env_start_idx));
				list_append(tokens, SPACE, NULL);
				if (str_start_idx == -1)
					state = DEFAULT;
				else
				{
					str_start_idx = i + 1;
					state = IN_STRING;
				}
			}
			if (line[i] == '"')
			{
				list_append(tokens, ENV_VAR, ft_substr(line, env_start_idx, i - env_start_idx));
				str_start_idx = i;
				state = IN_STRING;
			}
			if (line[i] == '\'')
			{
				list_append(tokens, ENV_VAR, ft_substr(line, env_start_idx, i - env_start_idx));
				str_start_idx = i;
				state = IN_RAW_STRING;
			}
		}
	}
	return (tokens);
}
