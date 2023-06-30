/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/01 01:34:01 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

t_state	in_command_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '<' || tokenizer->line[i] == '>'
		|| tokenizer->line[i] == '|' || tokenizer->line[i] == '$'
		|| tokenizer->line[i] == '\'' || tokenizer->line[i] == '"'
		|| tokenizer->line[i] == ' ')
	{
		tokens_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		tokenizer->i--;
		return (IN_DEFAULT);
	}
	else if (tokenizer->line[i + 1] == '\0')
	{
		tokens_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx + 1));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	return (IN_COMMAND);
}
