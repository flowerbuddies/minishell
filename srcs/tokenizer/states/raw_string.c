/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 17:39:49 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

t_state	in_raw_string_state(t_tokenizer *tokenizer, int i)
{
	if (tokenizer->line[i] == '\'')
	{
		list_append(tokenizer, STRING, ft_substr(tokenizer->line,
				tokenizer->str_start_idx, i - tokenizer->str_start_idx));
		tokenizer->str_start_idx = -1;
		return (IN_DEFAULT);
	}
	return (IN_RAW_STRING);
}

