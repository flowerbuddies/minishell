/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:19:33 by hunam             #+#    #+#             */
/*   Updated: 2023/06/23 18:54:37 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"
#include <stdlib.h>

static int	get_total_len(t_token *token)
{
	int		total_len;

	total_len = 0;
	while (token->type == STRING)
	{
		total_len += ft_strlen(token->data);
		token = token->next;
		if (!token)
			break ;
	}
	return (total_len);
}

static char	*get_total_str(t_tokenizer *tokenizer, t_token *first_string_token)
{
	t_token		*current;
	int			current_str_i;
	char		*total_str;
	int			total_str_i;
	const int	total_len = get_total_len(first_string_token);

	current = first_string_token;
	total_str = malloc(sizeof(char) * (total_len + 1));
	if (!total_str)
	{
		tokenizer->errored = true;
		return (NULL);
	}
	total_str_i = 0;
	while (current->type == STRING)
	{
		current_str_i = -1;
		while (current->data[++current_str_i])
			total_str[total_str_i++] = current->data[current_str_i];
		current = current->next;
		if (!current)
			break ;
	}
	total_str[total_str_i] = '\0';
	return (total_str);
}

static void	free_remaining_string_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current->type == STRING)
	{
		free(current->data);
		tokens = current->next;
		free(current);
		current = tokens;
		if (!current)
			break ;
	}
}

static void	free_strings_reattach(t_token *first_string_token, t_token *attach)
{
	free_remaining_string_tokens(first_string_token->next);
	first_string_token->next = attach;
}

void	concat_string_tokens(t_tokenizer *tokenizer)
{
	t_token	*current;
	t_token	*current_string;
	t_token	*first_string_token;
	char	*total_str;

	current = tokenizer->tokens;
	while (current)
	{
		if (current->type == STRING)
		{
			first_string_token = current;
			current_string = current;
			while (current_string->next && current_string->next->type == STRING)
				current_string = current_string->next;
			if (first_string_token != current_string)
			{
				total_str = get_total_str(tokenizer, first_string_token);
				free(first_string_token->data);
				first_string_token->data = total_str;
				free_strings_reattach(first_string_token, current_string->next);
			}
		}
		current = current->next;
	}
}
