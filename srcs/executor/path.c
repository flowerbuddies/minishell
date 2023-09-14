/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:26:35 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 20:11:45 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env_var.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include "tokenizer.h"
#include "builtin.h"
#include "executor.h"

static char	*direct_path(char *cmd)
{
	struct stat	path_stat;

	if (access(cmd, F_OK) == -1)
	{
		get_shell()->exit_status = not_found;
		print_error("command not found", cmd);
		return (NULL);
	}
	if (access(cmd, X_OK) == -1)
	{
		get_shell()->exit_status = not_executable;
		print_error("permission denied", cmd);
		return (NULL);
	}
	if (stat(cmd, &path_stat) == -1)
		action_failed("stat");
	if (!S_ISREG(path_stat.st_mode))
	{
		get_shell()->exit_status = not_executable;
		print_error("not a file", cmd);
		return (NULL);
	}
	return (ft_strdup(cmd));
}

char	*get_command_path(char *cmd)
{
	char	*path;

	if (ft_strchr(cmd, '/'))
		return (direct_path(cmd));
	path = find_cmd_in_path(cmd);
	if (path)
		return (path);
	get_shell()->exit_status = not_found;
	print_error("command not found", cmd);
	return (NULL);
}
