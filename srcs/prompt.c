/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/22 18:30:33 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "tokenizer.h"

void	prompt(void)
{
	t_tokenizer	tokenizer;

	while (42)
	{
		tokenizer.line = readline("MiniHell $ ");
		tokenize(&tokenizer);
		if (tokenizer.errored)
		{
			printf("Error: `malloc` managed to fail.\n");
			return ;
		}
		list_print(tokenizer.tokens);
		list_free(tokenizer.tokens);
		// TODO: this is very very likely temporary
		if (ft_strncmp(tokenizer.line, "exit", 4) == 0)
		{
			free(tokenizer.line);
			exit(0);
		}
		if (tokenizer.line[0])
			add_history(tokenizer.line);
		free(tokenizer.line);
	}
}
