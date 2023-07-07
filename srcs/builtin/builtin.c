/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 20:15:53 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include "minishell.h"
#include "libft.h"

bool	is_builtin(const char *cmd)
{
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	const int	builtin_lens[] = {4, 2, 3, 6, 5, 3, 4};
	const int	cmd_len = ft_strlen(cmd);
	int			i;

	i = -1;
	while (builtins[++i])
		if (cmd_len == builtin_lens[i]
			&& ft_strncmp(builtins[i], cmd, cmd_len) == 0)
			return (true);
	return (false);
}

void	execute_builtin(t_token *cmd)
{
	if (ft_strncmp(cmd->data, "echo", 4) == 0)
		echo(cmd->next);
	else if (ft_strncmp(cmd->data, "cd", 2) == 0)
		cd(cmd->next);
	else if (ft_strncmp(cmd->data, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd->data, "export", 6) == 0)
		export(cmd->next);
	else if (ft_strncmp(cmd->data, "unset", 5) == 0)
		unset(cmd->next);
	else if (ft_strncmp(cmd->data, "env", 3) == 0)
		env(cmd->next);
}
