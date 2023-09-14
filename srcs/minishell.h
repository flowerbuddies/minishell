/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:10:32 by mfm               #+#    #+#             */
/*   Updated: 2023/09/14 19:12:17 by hunam            ###   ########.fr       */
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

	bool			sigint;
	bool			sigquit;
	bool			heredoc_exited;
	bool			exit_needed;
}					g_shell;

void	action_failed(char *action);
bool	streq(const char *s1, const char *s2);
void	eprintf(const char *s1, const char *s2, const char *s3);

#endif
