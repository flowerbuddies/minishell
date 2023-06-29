/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:27:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/29 17:12:04 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include <stdlib.h>
#include <minishell.h>

static t_state	in_env_var_state_end(t_tokenizer *tokenizer, int i)
{
	char	*name;

	if (tokenizer->line[i] == '\'')
	{
		name = ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx);
		list_append(tokenizer, STRING, get_var(g_shell.vars, name)->value);
		free(name);
		return (tokenizer->str_start_idx = i, IN_RAW_STRING);
	}
	else if (tokenizer->line[i + 1] == '\0')
	{
		name = ft_substr(tokenizer->line,
				tokenizer->env_start_idx, i - tokenizer->env_start_idx + 1);
		list_append(tokenizer, STRING, get_var(g_shell.vars, name)->value);
		free(name);
		return (IN_DEFAULT);
	}
	return (IN_ENV_VAR);
}

t_state	in_env_var_state(t_tokenizer *tokenizer, int i)
{
	const char	*name = ft_substr(tokenizer->line,
			tokenizer->env_start_idx, i - tokenizer->env_start_idx);
	const t_var	*var = get_var(g_shell.vars, (char *) name);

	free((void *) name);
	if (tokenizer->line[i] == ' ')
	{
		list_append(tokenizer, STRING, var->value);
		if (tokenizer->str_start_idx == -1)
			return (list_append(tokenizer, SPACE, NULL), IN_DEFAULT);
		else
			return (tokenizer->str_start_idx = i, IN_STRING);
	}
	else if (tokenizer->line[i] == '"')
	{
		list_append(tokenizer, STRING, var->value);
		if (tokenizer->str_start_idx == -1)
			return (tokenizer->str_start_idx = i, IN_STRING);
		else
			return (IN_DEFAULT);
	}
	else
		return (in_env_var_state_end(tokenizer, i));
}
