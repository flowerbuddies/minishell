/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:19:33 by hunam             #+#    #+#             */
/*   Updated: 2023/06/22 16:03:49 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"
#include <stdlib.h>

static int	get_total_len(t_token *first_string_token)
{
	t_token	*current;
	int		total_len;

	current = first_string_token;
	total_len = 1;
	while (current->next && current->next->type == STRING)
	{
		total_len += ft_strlen(current->data);
		current = current->next;
	}
	total_len += ft_strlen(current->data);
	return (total_len);
}

static char	*get_total_str(t_token *first_string_token)
{
	t_token		*current;
	int			current_str_i;
	char		*total_str;
	int			total_str_i;
	const int	total_len = get_total_len(first_string_token);

	current = first_string_token;
	total_str = malloc(sizeof(char) * total_len);
	total_str_i = 0;
	if (!total_str)
		return (NULL);
	while (current->next && current->next->type == STRING)
	{
		current_str_i = -1;
		while (current->data[++current_str_i])
			total_str[total_str_i++] = current->data[current_str_i];
		current = current->next;
	}
	current_str_i = -1;
	while (current->data[++current_str_i])
		total_str[total_str_i++] = current->data[current_str_i];
	total_str[total_str_i] = '\0';
	return (total_str);
}

static void	free_remaining_tokens(t_token *tokens)
{
	if (tokens->next && tokens->next->type == STRING)
		free_remaining_tokens(tokens->next);
	free(tokens->data);
	free(tokens);
}

void	concat_string_tokens(t_token *tokens)
{
	t_token	*first_string_token;
	t_token	*current;
	t_token	*tmp;
	char	*total_str;

	while (tokens->next)
	{
		if (tokens->type == STRING)
		{
			first_string_token = tokens;
			current = tokens;
			while (current->next && current->next->type == STRING)
				current = current->next;
			if (first_string_token != current)
			{
				total_str = get_total_str(first_string_token);
				free(first_string_token->data);
				first_string_token->data = total_str;
				tmp = current->next;
				free_remaining_tokens(first_string_token->next);
				first_string_token->next = tmp;
			}
		}
		tokens = tokens->next;
	}
}
