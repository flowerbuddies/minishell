/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:39:02 by hunam             #+#    #+#             */
/*   Updated: 2023/09/10 18:05:35 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
# include "tokenizer.h"

// echo_cd_pwd.c
int		echo(t_token *cmd);
int		cd(t_token *cmd);
int		pwd(void);

// export_unset_env.c
int		export(t_token *cmd);
int		unset(t_token *cmd);
int		env(t_token *cmd);

// builtin.c
bool	try_builtin(t_token *cmd);
int		execute_builtin(t_token *cmd);

#endif
