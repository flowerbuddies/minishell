/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/30 18:49:57 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "tokenizer.h"
#include "syntax_checker.h"
#include "tree_constructor.h"

void	prompt(void)
{
	t_tokenizer	tokenizer;
	t_node		*ast;

	while (42)
	{
		tokenizer.line = readline("MiniHell $ ");
		tokenize(&tokenizer);
		{
			printf("Error: `malloc` managed to fail.\n");
			return ;
		}
		list_print(tokenizer.tokens); //TODO: rm
		if (check_syntax(&tokenizer))
		{
			ast = new_node(NULL);
			construct_ast(tokenizer.tokens, ast);
			print_ast(ast);
		}
		list_free(tokenizer.tokens);
		// TODO: rm
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
