/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 17:40:40 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>

static t_state	in_env_var_state_end(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx));
		return (tokenizer->str_start_idx = i, IN_RAW_STRING);
	}
	else if (tokenizer->line[i + 1] == '\0')
	{
		list_append(tokenizer, ENV_VAR, ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx + 1));
		return (IN_DEFAULT);
	}
	return (IN_ENV_VAR);
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
	else
		return (in_env_var_state_end(tokenizer, i));
}
