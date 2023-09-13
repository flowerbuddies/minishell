/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:10:32 by mfm               #+#    #+#             */
/*   Updated: 2023/09/12 20:18:31 by marmulle         ###   ########.fr       */
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

	bool			nl_needed;
	bool			exit_needed;
}					g_shell;

void	action_failed(char *action);
bool	streq(const char *s1, const char *s2);

#endif
