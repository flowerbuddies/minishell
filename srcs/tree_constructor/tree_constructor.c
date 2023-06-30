/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:20:54 by hunam             #+#    #+#             */
/*   Updated: 2023/07/01 01:34:11 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_constructor.h"
#include "tokenizer.h"
#include "libft.h" //TODO: rm

t_node	*new_node(t_node *parent)
{
	t_node	*out;

	out = malloc(sizeof(t_node));
	if (!out)
		return (NULL);
	out->type = _NOT_SET;
	out->data = NULL;
	out->parent = parent;
	out->left = NULL;
	out->right = NULL;
	return (out);
}

//TODO: maybe pass `t_token *tokens` instead
void	construct_ast(t_token *start, t_node *parent)
{
	t_token	*prev;
	t_token	*current;

	prev = NULL;
	current = start;
	while (current)
	{
		if (current->type == PIPE)
		{
			parent->type = PIPE;
			parent->right = new_node(parent);
			construct_ast(current->next, parent->right);
			if (prev)
				prev->next = NULL;
			parent->left = new_node(parent);
			construct_ast(start, parent->left);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}

	prev = NULL;
	current = start;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_OUT_APPEND)
		{
			parent->type = current->type;
			parent->right = new_node(parent);
			construct_ast(current->next, parent->right);
			if (prev)
				prev->next = NULL;
			parent->left = new_node(parent);
			construct_ast(start, parent->left);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	parent->type = STRING;
	parent->data = start;

	//TODO: heredoc actually exists
}

void	print_ast(t_node *first)
{
	if (!first)
		return ;
	if (first->type == PIPE)
		ft_printf("|\n");
	else if (first->type == REDIR_IN)
		ft_printf("<\n");
	else if (first->type == REDIR_OUT)
		ft_printf(">\n");
	else if (first->type == REDIR_OUT_APPEND)
		ft_printf(">>\n");
	else
		ft_printf("%s\n", first->data->data);
	print_ast(first->left);
	print_ast(first->right);
}

void	free_ast(t_node *first)
{
	if (!first)
		return ;
	free_ast(first->left);
	free_ast(first->right);
	if (first->data)
		tokens_free(first->data);
	free(first);
}
