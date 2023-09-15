/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:20:54 by hunam             #+#    #+#             */
/*   Updated: 2023/09/15 15:48:23 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_constructor.h"
#include "tokenizer.h"
#include "libft.h"

t_node	*new_node(void)
{
	t_node	*out;

	out = malloc(sizeof(t_node));
	if (!out)
		return (NULL);
	out->type = _NOT_SET;
	out->left = NULL;
	out->right = NULL;
	out->token = NULL;
	out->redirs = NULL;
	return (out);
}

void	append_token(t_token **current, t_token *token, t_type type)
{
	while (*current)
		current = &((*current)->next);
	*current = tokens_new();
	(*current)->type = type;
	(*current)->data = ft_strdup(token->data);
}

t_node	*extract_cmd(t_token *current)
{
	t_node	*out;

	out = new_node();
	out->type = STRING;
	while (current && !current->gate)
	{
		if (current->type == STRING)
			append_token(&out->token, current, current->type);
		else
			append_token(&out->redirs, current->next, current->type);
		if (current->type != STRING)
			current = current->next;
		current = current->next;
	}
	if (out->token == NULL)
	{
		out->token = tokens_new();
		out->token->type = STRING;
		out->token->data = ft_strdup("/usr/bin/true");
	}
	return (out);
}

t_node	*construct_ast(t_token *start)
{
	t_node	*out;
	t_token	*current;

	current = start;
	while (current && !current->gate)
	{
		if (current->type == PIPE)
		{
			out = new_node();
			out->type = PIPE;
			current->gate = true;
			out->left = construct_ast(start);
			out->right = construct_ast(current->next);
			return (out);
		}
		current = current->next;
	}
	return (extract_cmd(start));
}

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->token)
		tokens_free(node->token);
	if (node->redirs)
		tokens_free(node->redirs);
	free(node);
}
