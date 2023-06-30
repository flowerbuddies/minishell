/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:40:28 by mfm               #+#    #+#             */
/*   Updated: 2023/06/30 23:51:49 by hunam            ###   ########.fr       */
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

// env_var.c
void	init_env_vars(char **ev);

// setter.c
t_var	*new_var(char *name, char *value);
void	vars_append(t_var **vars, t_var *var);
void	vars_delete_at(t_var *vars, char *name);
void	vars_free(t_var *var);

// getter.c
t_var	*get_var(t_var *list, char *name);
void	print_var(t_var *var);
void	print_vars(t_var *vars);

#endif
