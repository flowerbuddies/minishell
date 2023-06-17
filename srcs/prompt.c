/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 13:58:43 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "tokenizer.h"

void	prompt(void)
{
	char	*line;
	t_token	*tokens;

	while (42)
	{
		line = readline("MiniHell $ ");
		tokens = tokenize(line);
		list_print(tokens);
		list_free(tokens);
		// TODO: this is very very likely temporary
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			exit(0);
		}
		if (line[0])
			add_history(line);
		free(line);
	}
}
