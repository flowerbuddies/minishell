/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/18 00:23:25 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "libft.h"

//TODO: think about merging COMMAND, RAW_STRING and STRING as we already get the env vars at this stage, they all just become strings

//TODO: think about a better name
static void	end(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->str_start_idx != -1)
		list_append(tokenizer->tokens, tokenizer->state + 6, ft_substr(
				tokenizer->line, tokenizer->str_start_idx,
				i - tokenizer->str_start_idx));
	else if (tokenizer->state == IN_ENV_VAR)
		list_append(tokenizer->tokens, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
}

t_token	*tokenize(const char *line)
{
	t_tokenizer	tokenizer;

	tokenizer.tokens = list_new();
	tokenizer.line = line;
	tokenizer.i = -1;
	tokenizer.state = DEFAULT;
	tokenizer.str_start_idx = -1;
	while (line[++tokenizer.i])
	{
		if (tokenizer.state == DEFAULT)
			tokenizer.state = default_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_COMMAND)
			tokenizer.state = in_command_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_RAW_STRING)
			tokenizer.state = in_raw_string_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_STRING)
			tokenizer.state = in_string_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_ENV_VAR)
			tokenizer.state = in_env_var_state(&tokenizer, tokenizer.i);
	}
	end(&tokenizer, tokenizer.i);
	return (tokenizer.tokens);
}
