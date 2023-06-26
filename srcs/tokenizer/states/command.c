/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 17:40:11 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

static t_state	in_command_state_end(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i + 1] == '\0')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx + 1));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	return (IN_COMMAND);
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
	else
		return (in_command_state_end(tokenizer, i));
}

