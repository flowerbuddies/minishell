/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:13:39 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/06 19:10:07 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "libft.h"

static void	encode_string(int write_end, char *string)
{
	int	string_len;

	string_len = ft_strlen(string);
	if (write(write_end, &string_len, sizeof(int)) == -1)
		action_failed("write");
	if (write(write_end, string, string_len) == -1)
		action_failed("write");
}

static void	encode_argv(int write_end, t_token *argv)
{
	int		argc;
	t_token	*current;

	argc = 0;
	current = argv;
	while (current)
	{
		current = current->next;
		argc++;
	}
	if (write(write_end, &argc, sizeof(int)) == -1)
		action_failed("write");
	while (argv)
	{
		encode_string(write_end, argv->data);
		argv = argv->next;
	}
}

static void	encode_envp(int write_end)
{
	t_var	*current;
	int		name_len;
	int		value_len;
	int		data_len;

	if (write(write_end, &g_shell.vars_len, sizeof(int)) == -1)
		action_failed("write");
	current = g_shell.vars;
	while (current)
	{
		name_len = ft_strlen(current->name);
		value_len = 0;
		if (current->value)
			value_len = ft_strlen(current->value);
		data_len = name_len + 1 + value_len;
		if (write(write_end, &data_len, sizeof(int)) == -1)
			action_failed("write");
		if (write(write_end, current->name, name_len) == -1)
			action_failed("write");
		if (write(write_end, "=", sizeof(char)) == -1)
			action_failed("write");
		if (write(write_end, current->value, value_len) == -1)
			action_failed("write");
		current = current->next;
	}
}

void	encode(int write_end, char *path, t_token *argv)
{
	encode_string(write_end, path);
	encode_argv(write_end, argv);
	encode_envp(write_end);
}
