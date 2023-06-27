/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:27 by hunam             #+#    #+#             */
/*   Updated: 2023/06/27 19:10:35 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checker.h"
#include <stdio.h>

static void	print_error(char *msg, int idx, char *idx_msg)
{
	if (idx != -1)
		printf("%*c^——%s\n", idx + 11, ' ', idx_msg);
	printf("\033[31;1mSyntax Error:\033[0m %s\n", msg);
}

bool	check_syntax(t_tokenizer *tokenizer)
{
	if (tokenizer->str_start_idx != -1)
		return (print_error("Missing string termination",
				tokenizer->str_start_idx - 1, "start of the string"), false);
	if (tokenizer->tokens && tokenizer->tokens[0].type == PIPE)
		return (print_error("Invalid pipe location", 0, "here"), false);
	return (true);
}
