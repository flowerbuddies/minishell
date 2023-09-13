/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:20:39 by hunam             #+#    #+#             */
/*   Updated: 2023/09/13 18:02:46 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_CONSTRUCTOR_H
# define TREE_CONSTRUCTOR_H

# include "tokenizer.h"

typedef struct s_node
{
	t_type			type;
	struct s_node	*left;
	struct s_node	*right;

	t_token			*token;
	t_token			*redir_in;
	t_token			*redir_out;
}	t_node;

// tree_constructor.c
t_node	*new_node(void);
t_node	*construct_ast(t_token *token);
void	print_ast(t_node *first);
void	free_ast(t_node *first);

#endif
