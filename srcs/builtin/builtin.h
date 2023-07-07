/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:39:02 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 20:16:46 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
# include "tokenizer.h"

// echo_cd_pwd.c
void	echo(t_token *cmd);
void	cd(t_token *cmd);
void	pwd(void);

// export_unset_env.c
void	export(t_token *cmd);
void	unset(t_token *cmd);
void	env(t_token *cmd);

// builtin.c
bool	is_builtin(const char *cmd);
void	execute_builtin(t_token *cmd);

#endif