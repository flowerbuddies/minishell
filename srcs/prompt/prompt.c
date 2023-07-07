/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 20:05:04 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "tokenizer.h"
#include "syntax_checker.h"
#include "tree_constructor.h"
#include "env_var.h"
#include "minishell.h"
#include "executor.h"

void	prompt(void)
{
	t_tokenizer	tokenizer;
	t_node		*ast;

	while (42)
	{
		tokenizer.line = readline("MiniHell $ ");
		if (!tokenizer.line[0])
			continue ;
		tokenize(&tokenizer);
		if (tokenizer.errored)
			action_failed("malloc");
		if (check_syntax(&tokenizer))
		{
			ast = new_node(NULL);
			construct_ast(tokenizer.tokens, ast);
			execute(ast);
			free_ast(ast);
		}
		else
			(set_exit_status(syntax_error), free(tokenizer.tokens));
		if (ft_strncmp(tokenizer.line, "exit", 4) == 0)
			(free(tokenizer.line), vars_free(g_shell.vars), exit(0));
		add_history(tokenizer.line);
		free(tokenizer.line);
	}
}
