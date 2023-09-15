/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:26:35 by hunam             #+#    #+#             */
/*   Updated: 2023/09/15 16:21:25 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "env_var.h"
#include "builtin.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

static void	free_2d(const char **obj)
{
	int	i;

	i = 0;
	while (obj[i])
		free((char *)obj[i++]);
	free(obj);
}

static char	*strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*out;
	size_t	i;
	size_t	j;

	if (!s1 || !s2 || !s3)
		return (NULL);
	out = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)
				+ 1));
	if (out == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		out[i++] = s1[j++];
	j = 0;
	while (s2[j])
		out[i++] = s2[j++];
	j = 0;
	while (s3[j])
		out[i++] = s3[j++];
	out[i] = '\0';
	return (out);
}

static char	*find_cmd_in_dir(const char *dir_name, char *cmd)
{
	DIR				*dir;
	struct dirent	*dir_entry;

	dir = opendir(dir_name);
	if (!dir)
		return (NULL);
	(readdir(dir), readdir(dir));
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		if (streq(cmd, dir_entry->d_name))
			return (closedir(dir), strjoin3(dir_name, "/", cmd));
		dir_entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

char	*find_cmd_in_path(char *cmd)
{
	const char	**dirs = (const char **)
		ft_split(vars_find("PATH")->value, ':');
	int			i;
	char		*cmd_path;

	if (!dirs)
		action_failed("ft_split");
	i = -1;
	while (dirs[++i])
	{
		cmd_path = find_cmd_in_dir(dirs[i], cmd);
		if (cmd_path)
			return (free_2d(dirs), cmd_path);
	}
	return (free_2d(dirs), NULL);
}
