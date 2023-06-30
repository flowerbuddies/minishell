/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/01 01:34:08 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

t_state	in_raw_string_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '\'')
	{
		tokens_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	return (IN_RAW_STRING);
}
