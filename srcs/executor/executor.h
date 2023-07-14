/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:02:15 by hunam             #+#    #+#             */
/*   Updated: 2023/07/14 18:52:48 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tree_constructor.h"
# include "env_var.h"

// executor.c
int		execute(t_node *ast);
int		execute_command(t_token *command);

// argv_envp.c
char	**get_argv(t_token *cmd);
char	**get_envp(t_var *env_vars);

//path.c
char	*get_command_path(char *cmd);

#endif
