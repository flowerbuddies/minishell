/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/01 01:33:31 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "tokenizer.h"
#include "libft.h"

static void	init_tokenizer(t_tokenizer *tokenizer)
{
	tokenizer->errored = false;
	tokenizer->tokens = tokens_new(tokenizer);
	if (tokenizer->errored)
		return ;
	tokenizer->i = -1;
	tokenizer->state = IN_DEFAULT;
	tokenizer->str_start_idx = -1;
}

void	tokenize(t_tokenizer *tokenizer)
{
	init_tokenizer(tokenizer);
	while (tokenizer->line[++tokenizer->i])
	{
		if (tokenizer->state == IN_DEFAULT)
			tokenizer->state = in_default_state(tokenizer, tokenizer->i);
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
	evaluate_env_vars(tokenizer);
	concat_string_tokens(tokenizer);
	delete_space_tokens(tokenizer);
}
