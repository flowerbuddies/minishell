/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:39:02 by hunam             #+#    #+#             */
/*   Updated: 2023/09/12 20:25:14 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
# include "tokenizer.h"

// echo_cd_pwd.c
void	echo(t_token *cmd);
void	cd(t_token *cmd, bool is_parent);
void	pwd(void);

// unset_env_exit.c
void	unset(t_token *cmd);
void	env(void);
void	exit_builtin(t_token *cmd);

// export.c
void	export(t_token *cmd, bool is_parent);

// builtin.c
bool	is_builtin(t_token *cmd);
void	execute_builtin(t_token *cmd, bool is_parent);

// utils.c
int		len2d(char **array);
void	free2d(char **array);

#endif
