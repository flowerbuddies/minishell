/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:40:28 by mfm               #+#    #+#             */
/*   Updated: 2023/07/01 16:20:53 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VAR_H
# define ENV_VAR_H

# include <stdbool.h>

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
	struct s_var	*prev;
}					t_var;

//env_var.c
void	init_env_vars(char **ev);
void	set_last_exit_status(char *value);

//linked_list/setter.c
t_var	*vars_new(char *name, char *value);
void	vars_append(t_var **vars, t_var *var);
void	vars_delete_at(t_var *vars, char *name);
void	vars_free(t_var *var);

//linked_list/getter.c
t_var	*vars_find(t_var *list, char *name);
void	vars_print(t_var *vars);

#endif
