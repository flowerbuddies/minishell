/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:39:02 by hunam             #+#    #+#             */
/*   Updated: 2023/07/10 19:38:48 by hunam            ###   ########.fr       */
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
bool	is_builtin(const char *cmd);
int		execute_builtin(t_token *cmd);

#endif