/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 15:37:48 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "tokenizer.h"
#include "syntax_checker.h"
#include "tree_constructor.h"
#include "env_var.h"
#include "minishell.h"
#include "executor.h"
#include "signals.h"
#include "builtin.h"
#include <signal.h>

//TODO: slipt this function into multiple
void	prompt(void)
{
	t_tokenizer	tokenizer;
	t_node		*ast;

	while (42)
	{
		signal(SIGINT, sig_interactive_mode);
		signal(SIGQUIT, SIG_IGN);
		if (get_shell()->nl_needed)
		{
			ft_printf("\n"); // TODO: enable for SIGQUIT
			get_shell()->nl_needed = false;
		}
		tokenizer.line = readline("MiniHell $ ");
		if (!tokenizer.line)
			(vars_free(get_shell()->vars), exit(get_shell()->exit_status));
		if (!tokenizer.line[0])
		{
			free(tokenizer.line);
			continue ;
		}
		tokenize(&tokenizer);
		if (!tokenizer.tokens)
		{
			free(tokenizer.line);
			continue ;
		}
		if (tokenizer.errored) //TODO: replace this by individual action_failed
			action_failed("tokenize's mallocs");
		if (check_syntax(&tokenizer))
		{
			ast = construct_ast(tokenizer.tokens);
			signal(SIGINT, sig_non_interactive_mode);
			signal(SIGQUIT, sig_non_interactive_mode);
			execute(ast);
			free_ast(ast);
			// TODO: `ls |` leaks --(mark) seems not to leak anymore
		}
		else
			get_shell()->exit_status = syntax_error;
		tokens_free(tokenizer.tokens);
		(add_history(tokenizer.line), free(tokenizer.line));
		if (get_shell()->exit_needed)
			(vars_free(get_shell()->vars), exit(get_shell()->exit_status));
	}
}
