/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:02:15 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 18:37:06 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tree_constructor.h"

// executor.c
void	execute(t_node *ast);
void	execute_command(t_token *command);
void	child_main(int comm[2]);

// encode.c
void	encode(int write_end, char *path, t_token *argv);

// decode.c
char	*decode_string(int read_end);
char	**decode_array(int read_end);

//path.c
char	*get_command_path(t_token *cmd);

#endif
