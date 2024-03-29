/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:02:15 by hunam             #+#    #+#             */
/*   Updated: 2023/09/13 18:19:09 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tree_constructor.h"
# include "env_var.h"

# define DEFAULT_FILE_PERMISSIONS 0644
# define READ_END 0
# define WRITE_END 1

typedef struct s_child
{
	char	*path;
	t_token	*cmd;
	int		io[2];
	bool	redir_in_needed;
	bool	redir_out_needed;
}	t_child;

// executor.c
void	execute(t_node *node);
void	execute_command(t_node *node);
void	print_error(char *msg, char *file_name);
void	execute_pipe(t_node *node);

// argv_envp.c
char	**get_argv(t_token *cmd);
char	**get_envp(t_var *env_vars);

// path.c
char	*get_command_path(char *cmd);

// redirection.c
bool	execute_redir(t_token *current);
int		open_file(int fd_to_close, t_type type, char *file_name);

#endif
