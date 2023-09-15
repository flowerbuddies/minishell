/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:53:49 by mfm               #+#    #+#             */
/*   Updated: 2023/09/15 15:25:23 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "tokenizer.h"

static void	increment_shlvl(void)
{
	const t_var	*shlvl = vars_find("SHLVL");
	const int	current_lvl = ft_atoi(shlvl->value);

	vars_delete_at("SHLVL");
	vars_append(vars_new(ft_strdup("SHLVL"), ft_itoa(current_lvl + 1)));
}

void	set_underscore_env_var(t_token *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	vars_delete_at("_");
	vars_append(vars_new(ft_strdup("_"), ft_strdup(cmd->data)));
}

void	init_env_vars(char **ev)
{
	char	**splits;
	int		len;

	get_shell()->vars_len = 0;
	get_shell()->vars = NULL;
	while (*ev)
	{
		splits = ft_split(*ev, '=');
		if (!splits)
			action_failed("ft_split");
		len = 0;
		while (splits[len])
			len++;
		if (len == 1 || len == 2)
			vars_append(vars_new(splits[0], splits[1]));
		else
			while (--len >= 0)
				free(splits[len]);
		free(splits);
		ev++;
	}
	increment_shlvl();
}
