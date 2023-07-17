/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:02:15 by hunam             #+#    #+#             */
/*   Updated: 2023/07/17 17:39:38 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tree_constructor.h"
# include "env_var.h"

# define DEFAULT_FILE_PERMISSIONS 0644
# define READ_ONLY_PERMISSIONS 0444

// executor.c
int		execute(t_node *ast, int io[2], bool has_pipe, bool has_redir_in);
int		execute_command(t_token *command, int io[2], bool has_pipe, bool has_redir_in);
void	child_main(char *path, char **argv, char **envp, int io[2], bool has_pipe, bool has_redir_in);

// argv_envp.c
char	**get_argv(t_token *cmd);
char	**get_envp(t_var *env_vars);

//path.c
char	*get_command_path(char *cmd);

// redirection.c
int		execute_pipe(t_node *node, int io[2]);
int		execute_redir_out(t_node *node, int io[2]);
int		execute_redir_in(t_node *node, int io[2]);

#endif
