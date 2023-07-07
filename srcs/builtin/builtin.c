/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 01:53:03 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdlib.h>

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

void	execute_builtin(const char *cmd)
{
	//TODO
	(void) cmd;
}
