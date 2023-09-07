/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/09/07 18:56:34 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "tokenizer.h"
#include "syntax_checker.h"
#include "tree_constructor.h"
#include "env_var.h"
#include "minishell.h"
#include "executor.h"

//TODO: slipt this function into multiple
void	prompt(void)
{
	t_tokenizer		tokenizer;
	t_node			*ast;
	// const int		dupped_in = dup(STDIN_FILENO);

	while (42)
	{
		tokenizer.line = readline("MiniHell $ ");
		if (!tokenizer.line)
			(vars_free(g_shell.vars), exit(0));
		if (!tokenizer.line[0])
			continue ;
		tokenize(&tokenizer);
		if (tokenizer.errored) //TODO: replace this by individual action_failed
			action_failed("tokenize's mallocs");
		if (check_syntax(&tokenizer))
		{
			ast = new_node(NULL);
			construct_ast(tokenizer.tokens, ast);
			execute(ast);
			// if (dup2(dupped_in, STDIN_FILENO) == -1)
			// 	action_failed("dup2");
			free_ast(ast); 
		}
		else
			(free(tokenizer.tokens), g_shell.exit_status = syntax_error);
		if (streq(tokenizer.line, "exit"))
			(free(tokenizer.line), vars_free(g_shell.vars),
				exit(g_shell.exit_status));
		(add_history(tokenizer.line), free(tokenizer.line));
		g_shell.stop_child = false;
	}
}
