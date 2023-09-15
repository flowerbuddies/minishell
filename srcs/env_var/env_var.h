/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:40:28 by mfm               #+#    #+#             */
/*   Updated: 2023/09/15 16:21:28 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include "tokenizer.h"
# include <stdbool.h>

typedef enum e_exit_status
{
	success = 0,
	failure = 1,
	invalid_usage = 2,
	not_found = 127,
	not_executable = 126,
	syntax_error = 258,
	signal_base = 128,
}	t_exit_status;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;
}					t_var;

//env_var.c
void	set_underscore_env_var(t_token *cmd);
void	init_env_vars(char **ev);

//linked_list/setter.c
t_var	*vars_new(char *name, char *value);
void	vars_append(t_var *var);
void	vars_delete_at(char *name);
void	vars_free(t_var *var);

//linked_list/getter.c
t_var	*vars_find(char *name);
void	vars_print(bool prepend_declare);

//path.c
char	*find_cmd_in_path(char *cmd);

#endif
