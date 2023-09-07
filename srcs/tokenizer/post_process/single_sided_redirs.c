/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_sided_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:23:45 by hunam             #+#    #+#             */
/*   Updated: 2023/07/19 21:08:10 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"
#include "executor.h"
#include "minishell.h"

static bool	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == REDIR_OUT_APPEND);
}

static int	*init_int_arr(int len)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * len);
	if (!arr)
		action_failed("malloc");
	i = -1;
	while (++i < len)
		arr[i] = -1;
	return (arr);
}

static void	handle_redir(t_tokenizer *tokenizer, int i,
	int	*to_be_removed, int *to_be_removed_i)
{
	int		fd;
	t_token	*current;

	current = tokens_at(tokenizer->tokens, i);
	fd = open_file(-1, current->type, current->next->data);
	close(fd);
	if (fd != -1)
	{
		current->type = STRING;
		current->data = ft_strdup("/usr/bin/true");
	}
	else
	{
		current->type = STRING;
		current->data = ft_strdup("/usr/bin/false");
	}
	while (current->next && current->next->type == STRING)
	{
		to_be_removed[(*to_be_removed_i)++] = ++i;
		current = current->next;
	}
}

void	single_sided_redirs(t_tokenizer *tokenizer)
{
	t_token	*prev;
	t_token	*current;
	int		i;
	int		*to_be_removed;
	int		to_be_removed_i;

	prev = NULL;
	current = tokenizer->tokens;
	i = 0;
	to_be_removed = init_int_arr(ft_strlen(tokenizer->line));
	to_be_removed_i = 0;
	while (current)
	{
		if (is_redir(current->type) && (!prev || prev->type == PIPE)
			&& current->next)
			handle_redir(tokenizer, i, to_be_removed, &to_be_removed_i);
		prev = current;
		if (current)
			current = current->next;
		i++;
	}
	while (to_be_removed_i > 0)
		tokens_delete_at(tokenizer, to_be_removed[--to_be_removed_i]);
	free(to_be_removed);
}
