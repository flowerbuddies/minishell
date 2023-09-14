/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:14:03 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 17:24:55 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include "libft.h"
#include "signals.h"
#include "executor.h"

static char	*strjoin(char *s1, char *s2)
{
	char	*out;

	if (!s1 && !s2)
		out = ft_strdup("");
	else if (!s1)
		out = ft_strdup(s2);
	else if (!s2)
		out = ft_strdup(s1);
	else
		out = ft_strjoin(s1, s2);
	if (!out)
		action_failed("strjoin");
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (out);
}

static char	*heredoc(char *delim)
{
	char		*input;
	char		*line;
	const int	dupped_stdin = dup(STDIN_FILENO);

	input = NULL;
	signal(SIGINT, sig_heredoc_mode);
	while (42)
	{
		line = readline("heredoc> ");
		if (!line || streq(line, delim))
		{
			if (line)
				free(line);
			input = strjoin(input, NULL);
			break ;
		}
		input = strjoin(input, strjoin(line, ft_strdup("\n")));
	}
	free(delim);
	dup2(dupped_stdin, STDIN_FILENO);
	signal(SIGINT, sig_interactive_mode);
	return (input);
}

void	heredocs_prompt_user_input(t_tokenizer *tokenizer)
{
	t_token	*current;

	current = tokenizer->tokens;
	while (current)
	{
		if (current->type == HEREDOC
			&& current->next && current->next->type == STRING)
				current->next->data = heredoc(current->next->data);
		current = current->next;
	}
}
