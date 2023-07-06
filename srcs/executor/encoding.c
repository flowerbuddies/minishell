/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:13:39 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/04 00:04:01 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "libft.h"

char	**decode(int read_end)
{
	char	**array;
	int		array_len;
	int		elem_len;
	int		i;

	if (read(read_end, &array_len, sizeof(int)) == -1)
		action_failed("read");
	array = malloc(sizeof(char *) * (array_len + 1));
	if (!array)
		action_failed("malloc");
	array[array_len] = NULL;
	i = -1;
	while (++i < array_len)
	{
		if (read(read_end, &elem_len, sizeof(int)) == -1)
			action_failed("read");
		array[i] = malloc(sizeof(char) * (elem_len + 1));
		if (!array[i])
			action_failed("malloc");
		if (read(read_end, array[i], elem_len) == -1)
			action_failed("read");
		array[i][elem_len] = '\0';
	}
	return (array);
}

static void	encode_argv(int write_end, t_token *argv)
{
	int		argc;
	int		data_len;
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
		data_len = ft_strlen(argv->data);
		if (write(write_end, &data_len, sizeof(int)) == -1)
			action_failed("write");
		if (write(write_end, argv->data, data_len) == -1)
			action_failed("write");
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

void	encode(int write_end, t_token *argv)
{
	encode_argv(write_end, argv);
	encode_envp(write_end);
}
