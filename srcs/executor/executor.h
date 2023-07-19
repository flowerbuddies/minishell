/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:02:15 by hunam             #+#    #+#             */
/*   Updated: 2023/07/19 18:44:24 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "tree_constructor.h"
# include "env_var.h"

# define DEFAULT_FILE_PERMISSIONS 0644

typedef struct s_child
{
	char	*path;
	t_token	*cmd;
	int		status_code;
	int		io[2];
	bool	redir_in_needed;
	bool	redir_out_needed;
}	t_child;

// executor.c
int		execute(t_node *ast, int io[2],
			bool redir_in_needed, bool redir_out_needed);
int		execute_command(t_token *command, int io[2],
			bool redir_in_needed, bool redir_out_needed);
void	child_main(t_child *child);
void	print_error(char *msg, char *file_name);
int		execute_pipe(t_node *node, int io[2]);

// argv_envp.c
char	**get_argv(t_token *cmd);
char	**get_envp(t_var *env_vars);

// path.c
char	*get_command_path(char *cmd);

// redirection.c
int		open_file(int fd_to_close, t_type type, char *file_name);
int		execute_redir_out(t_node *node, int io[2], bool redir_out_needed);
int		execute_redir_in(t_node *node, int io[2], bool redir_out_needed);

#endif
