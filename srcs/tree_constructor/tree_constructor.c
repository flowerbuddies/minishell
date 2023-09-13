/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:20:54 by hunam             #+#    #+#             */
/*   Updated: 2023/09/13 22:40:03 by hunam            ###   ########.fr       */
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
	(*current)->data = ft_strdup(token->data); //TODO: possible leak when called from extract_cmd
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
	if (out->token == NULL) //TODO: what's this? possible leak when setting data?
	{
		out->token = tokens_new();
		out->token->type = STRING;
		out->token->data = ft_strdup("/usr/bin/true");
	}
	return (out);
}

t_node	*extract_pipes(t_token *start)
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
			out->left = extract_pipes(start);
			out->right = extract_pipes(current->next);
			return (out);
		}
		current = current->next;
	}
	return (extract_cmd(start));
}

t_node	*construct_ast(t_token *start)
{
	return (extract_pipes(start));
	//TODO: check for leaks
}

// void	print_ast(t_node *first)
// {
// 	t_token	*tmp_token;
// 	t_node	*tmp_node;

// 	if (!first)
// 		return ;
// 	if (first->type == PIPE)
// 		ft_printf("|\n");
// 	else if (first->type == STRING)
// 	{
// 		tmp_token = first->token;
// 		while (tmp_token)
// 		{
// 			ft_printf("%s ", tmp_token->data);
// 			tmp_token = tmp_token->next;
// 		}
// 		ft_printf("\n\t");
// 		tmp_node = first->redir_out;
// 		while (tmp_node)
// 		{
// 			ft_printf("> %s ", tmp_node->token->data);
// 			tmp_node = tmp_node->redir_out;
// 		}
// 		ft_printf("\n");
// 	}
// 	print_ast(first->left);
// 	print_ast(first->right);
// }

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
