/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:26:35 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 18:53:02 by hunam            ###   ########.fr       */
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

static void	*print_error(char *msg, char *cmd)
{
	ft_putstr_fd("\e[31;1mError:\e[0m `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("`: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	return (NULL);
}

static char	*direct_path(char *cmd)
{
	struct stat	path_stat;

	if (access(cmd, F_OK) == -1)
	{
		g_shell.exit_status = not_found;
		return (print_error("command not found", cmd));
	}
	if (access(cmd, X_OK) == -1)
	{
		g_shell.exit_status = not_executable;
		return (print_error("permission denied", cmd));
	}
	if (stat(cmd, &path_stat) == -1)
		action_failed("stat");
	if (!S_ISREG(path_stat.st_mode))
	{
		g_shell.exit_status = not_executable;
		return (print_error("not a file", cmd));
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
	g_shell.exit_status = not_found;
	return (print_error("command not found", cmd));
}
