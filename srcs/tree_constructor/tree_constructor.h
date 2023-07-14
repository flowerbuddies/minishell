/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:20:39 by hunam             #+#    #+#             */
/*   Updated: 2023/07/14 16:20:45 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_CONSTRUCTOR_H
# define TREE_CONSTRUCTOR_H

# include "tokenizer.h"

typedef struct s_node
{
	t_type			type;
	t_token			*token;
	struct s_node	*parent; //TODO: maybe rm
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

// tree_constructor.c
t_node	*new_node(t_node *parent);
void	construct_ast(t_token *token, t_node *out);
void	print_ast(t_node *first);
void	free_ast(t_node *first);

#endif
