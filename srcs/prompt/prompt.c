/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/09/15 16:19:35 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "tree_constructor.h"
#include "syntax_checker.h"
#include "libft.h"
#include "signals.h"
#include "executor.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	exit_prompt(void)
{
	printf("exit\n");
	vars_free(get_shell()->vars);
	exit(get_shell()->exit_status);
}

static void	signal_step(void)
{
	signal(SIGINT, sig_interactive_mode);
	signal(SIGQUIT, SIG_IGN);
	if (get_shell()->sigint)
	{
		ft_printf("\n");
		get_shell()->sigint = false;
	}
	else if (get_shell()->sigquit)
	{
		ft_printf("Quit: 3\n");
		rl_redisplay();
		get_shell()->sigquit = false;
	}
}

static bool	tokenize_step(t_tokenizer *tokenizer)
{
	tokenizer->line = readline("MiniHell $ ");
	if (!tokenizer->line)
		exit_prompt();
	if (!tokenizer->line[0])
	{
		free(tokenizer->line);
		return (true);
	}
	tokenize(tokenizer);
	if (!tokenizer->tokens)
	{
		free(tokenizer->line);
		return (true);
	}
	if (tokenizer->errored)
		action_failed("tokenize");
	return (false);
}

static void	execute_step(t_tokenizer *tokenizer)
{
	t_node		*ast;

	if (!get_shell()->heredoc_exited && check_syntax(tokenizer))
	{
		ast = construct_ast(tokenizer->tokens);
		signal(SIGINT, sig_non_interactive_mode);
		signal(SIGQUIT, sig_non_interactive_mode);
		execute(ast);
		free_ast(ast);
	}
	else if (get_shell()->heredoc_exited)
	{
		get_shell()->heredoc_exited = false;
		get_shell()->exit_status = failure;
	}
	else
		get_shell()->exit_status = syntax_error;
	tokens_free(tokenizer->tokens);
}

void	prompt(void)
{
	t_tokenizer	tokenizer;

	while (42)
	{
		signal_step();
		if (tokenize_step(&tokenizer))
			continue ;
		execute_step(&tokenizer);
		add_history(tokenizer.line);
		free(tokenizer.line);
		if (get_shell()->exit_needed)
			exit_prompt();
	}
}
