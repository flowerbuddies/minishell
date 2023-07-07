/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:26:35 by hunam             #+#    #+#             */
/*   Updated: 2023/07/07 20:05:04 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env_var.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include "builtin.h"
#include "tokenizer.h"

static char	*direct_path(char *cmd)
{
	struct stat	path_stat;

	if (access(cmd, F_OK) == -1)
	{
		printf("\e[31;1mError:\e[0m command `%s` not found\n", cmd);
		return (set_exit_status(not_found), NULL);
	}
	if (access(cmd, X_OK) == -1)
	{
		printf("\e[31;1mError:\e[0m permission denied on `%s`\n",
			cmd);
		return (set_exit_status(not_executable), NULL);
	}
	if (stat(cmd, &path_stat) == -1)
		action_failed("stat");
	if (!S_ISREG(path_stat.st_mode))
	{
		printf("\e[31;1mError:\e[0m `%s` is not a file\n", cmd);
		return (set_exit_status(not_executable), NULL);
	}
	return (ft_strdup(cmd));
}

char	*get_command_path(t_token *cmd)
{
	char	*tmp;

	if (ft_strchr(cmd->data, '/'))
		return (direct_path(cmd->data));
	if (is_builtin(cmd->data))
		return (execute_builtin(cmd), NULL);
	tmp = find_cmd_in_path(cmd->data);
	if (tmp)
		return (tmp);
	printf("\e[31;1mError:\e[0m command `%s` not found\n", cmd->data);
	set_exit_status(not_found);
	return (NULL);
}
