/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:02:15 by hunam             #+#    #+#             */
/*   Updated: 2023/07/03 18:45:01 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tree_constructor.h"

// executor.c
void	execute(t_node *ast);
void	execute_command(t_token *command);
void	child_main(void);

// encoding.c
void	encode(int write_end, t_token *argv);
char	**decode(int read_end);

#endif
