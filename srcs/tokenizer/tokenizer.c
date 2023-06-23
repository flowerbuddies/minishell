/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:05:26 by hunam             #+#    #+#             */
/*   Updated: 2023/06/23 17:15:30 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "libft.h"

void	tokenize(t_tokenizer *tokenizer)
{
	tokenizer->errored = false;
	tokenizer->tokens = list_new(tokenizer);
	if (tokenizer->errored)
		return ;
	tokenizer->i = -1;
	tokenizer->state = IN_DEFAULT;
	tokenizer->str_start_idx = -1;
	while (tokenizer->line[++tokenizer->i])
	{
		if (tokenizer->state == IN_DEFAULT)
			tokenizer->state = default_state(tokenizer, tokenizer->i);
		else if (tokenizer->state == IN_COMMAND)
			tokenizer->state = in_command_state(tokenizer, tokenizer->i);
		else if (tokenizer->state == IN_RAW_STRING)
			tokenizer->state = in_raw_string_state(tokenizer, tokenizer->i);
		else if (tokenizer->state == IN_STRING)
			tokenizer->state = in_string_state(tokenizer, tokenizer->i);
		else if (tokenizer->state == IN_ENV_VAR)
			tokenizer->state = in_env_var_state(tokenizer, tokenizer->i);
		if (tokenizer->errored)
			return ;
	}
	concat_string_tokens(tokenizer);
}
