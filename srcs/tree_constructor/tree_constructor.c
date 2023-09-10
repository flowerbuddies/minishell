/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:20:54 by hunam             #+#    #+#             */
/*   Updated: 2023/09/10 21:09:56 by hunam            ###   ########.fr       */
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
	out->redir_in = NULL;
	out->redir_out = NULL;
	return (out);
}

void	append_redir_in(t_node *out, t_type type, t_token *redir_str)
{
	while (out->redir_in)
		out = out->redir_in;
	out->redir_in = new_node();
	out->redir_in->type = type;
	out->redir_in->token = redir_str;
}

void	append_redir_out(t_node *out, t_type type, t_token *redir_str)
{
	while (out->redir_out)
		out = out->redir_out;
	out->redir_out = new_node();
	out->redir_out->type = type;
	out->redir_out->token = redir_str;
}

void	append_arg(t_node *out, t_token *arg_str)
{
	t_token	**current;

	current = &out->token;
	while (*current)
		current = &((*current)->next);

	*current = tokens_new();
	(*current)->type = STRING;
	(*current)->data = ft_strdup(arg_str->data);
}

t_node	*extract_cmd(t_token *current)
{
	t_node	*out;

	out = new_node();
	out->type = STRING;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == HEREDOC)
			append_redir_in(out, current->type, current->next);
		else if (current->type == REDIR_OUT
			|| current->type == REDIR_OUT_APPEND)
			append_redir_out(out, current->type, current->next);
		else
			append_arg(out, current);
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

t_node	*extract_pipes(t_token *start)
{
	t_node	*out;
	t_token	*prev;
	t_token	*current;

	out = new_node();
	prev = NULL;
	current = start;
	while (current)
	{
		if (current->type == PIPE)
		{
			out->type = PIPE;
			out->right = extract_pipes(current->next);
			if (prev)
				prev->next = NULL;
			out->left = extract_pipes(start);
			free(current);
			return (out);
		}
		prev = current;
		current = current->next;
	}
	free(out);
	return (extract_cmd(start));
}

t_node	*construct_ast(t_token *start)
{
	return (extract_pipes(start));
	//TODO: check for leaks
}

void	print_ast(t_node *first)
{
	t_token	*tmp_token;
	t_node	*tmp_node;

	if (!first)
		return ;
	if (first->type == PIPE)
		ft_printf("|\n");
	else if (first->type == STRING)
	{
		tmp_token = first->token;
		while (tmp_token)
		{
			ft_printf("%s ", tmp_token->data);
			tmp_token = tmp_token->next;
		}
		ft_printf("\n\t");
		tmp_node = first->redir_out;
		while (tmp_node)
		{
			ft_printf("> %s ", tmp_node->token->data);
			tmp_node = tmp_node->redir_out;
		}
		ft_printf("\n");
	}
	print_ast(first->left);
	print_ast(first->right);
}

void	free_ast(t_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	// free_ast(node->redir_in);
	// free_ast(node->redir_out);
	//TODO: `> omg /bin/echo hi > out` leaks
	if (node->token)
		tokens_free(node->token);
	free(node);
}
