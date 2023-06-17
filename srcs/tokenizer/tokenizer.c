/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 14:22:13 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "libft.h"

t_token	*tokenize(const char *line)
{
	t_token		*tokens;
	int			i;
	t_state		state;
	int			string_beg;

	tokens = list_new();
	i = -1;
	state = DEFAULT;
	while (line[++i])
	{
		if (state == DEFAULT)
		{
			if (line[i] == '<')
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
				string_beg = i + 1;
				state = IN_RAW_STRING;
			}
		}
		else if (state == IN_RAW_STRING)
		{
			if (line[i] == '\'')
			{
				list_append(tokens, RAW_STRING, ft_substr(line, string_beg, i - string_beg));
				state = DEFAULT;
			}
		}
	}
	return (tokens);
}
