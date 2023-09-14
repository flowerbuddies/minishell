/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:13:39 by marmulle          #+#    #+#             */
/*   Updated: 2023/09/14 15:37:16 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "libft.h"

char	**get_argv(t_token *cmd)
{
	int		i;
	int		argc;
	char	**argv;
	t_token	*current;

	i = -1;
	argc = 0;
	current = cmd;
	while (current)
	{
		argc++;
		current = current->next;
	}
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		action_failed("malloc");
	while (cmd)
	{
		argv[++i] = ft_strdup(cmd->data);
		if (!argv[i])
			action_failed("ft_strdup");
		cmd = cmd->next;
	}
	argv[argc] = NULL;
	return (argv);
}

char	**get_envp(t_var *env_vars)
{
	int		i;
	char	**envp;
	int		name_len;
	int		value_len;

	i = -1;
	envp = malloc(sizeof(char *) * (get_shell()->vars_len + 1));
	if (!envp)
		action_failed("malloc");
	while (env_vars)
	{
		name_len = ft_strlen(env_vars->name);
		value_len = 0;
		if (env_vars->value)
			value_len = ft_strlen(env_vars->value);
		envp[++i] = ft_calloc(name_len + 1 + value_len + 1, sizeof(char));
		if (!envp[i])
			action_failed("malloc");
		ft_memmove(envp[i], env_vars->name, name_len);
		envp[i][name_len] = '=';
		ft_memmove(&envp[i][name_len + 1], env_vars->value, value_len);
		env_vars = env_vars->next;
	}
	envp[get_shell()->vars_len] = NULL;
	return (envp);
}
