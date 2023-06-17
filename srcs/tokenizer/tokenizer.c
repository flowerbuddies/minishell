/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 21:40:04 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

//TODO: think about merging COMMAND, RAW_STRING and STRING as we already get the env vars at this stage, they all just become strings

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
			tokenizer.state = state_default(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_COMMAND)
			tokenizer.state = in_command_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_RAW_STRING)
			tokenizer.state = in_raw_string_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_STRING)
			tokenizer.state = in_string_state(&tokenizer, tokenizer.i);
		else if (tokenizer.state == IN_ENV_VAR)
			tokenizer.state = in_env_var_state(&tokenizer, tokenizer.i);
	}
	return (tokenizer.tokens);
}
