/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/01 01:34:07 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

static t_state	in_env_var_state_end(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i + 1] == '\0')
	{
		tokens_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx + 1));
		return (IN_DEFAULT);
	}
	return (IN_ENV_VAR);
}

t_state	in_env_var_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '"')
	{
		if (i - tokenizer->env_start_idx == 0)
			return (tokens_append(tokenizer, STRING, ft_strdup("$")), IN_DEFAULT);
		tokens_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		return (tokenizer->str_start_idx = -1, IN_DEFAULT);
	}
	else if (tokenizer->line[i] == '<' || tokenizer->line[i] == '>'
		|| tokenizer->line[i] == '|' || tokenizer->line[i] == '$'
		|| tokenizer->line[i] == '\'' || tokenizer->line[i] == ' ')
	{
		if (i - tokenizer->env_start_idx == 0)
			return (tokens_append(tokenizer, STRING, ft_strdup("$")), IN_DEFAULT);
		tokens_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		if (tokenizer->str_start_idx != -1)
			return (tokenizer->str_start_idx = i, IN_STRING);
		else
			return (tokenizer->i--, IN_DEFAULT);
	}
	else
		return (in_env_var_state_end(tokenizer, i));
}
