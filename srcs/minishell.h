/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:10:32 by mfm               #+#    #+#             */
/*   Updated: 2023/07/24 19:40:06 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env_var.h"
# include <unistd.h>

struct s_shell
{
	t_var			*vars;
	int				vars_len;

	t_exit_status	exit_status;

	pid_t			child_pid;
	bool			stop_child;
	bool			is_child_running;

	pid_t			pids[100];
	int				pids_idx;
}					g_shell;

void	action_failed(char *action);
bool	streq(const char *s1, const char *s2);

#endif
