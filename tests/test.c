/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:31:53 by hunam             #+#    #+#             */
/*   Updated: 2023/07/03 17:08:01 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "test.h"
#include "../srcs/minishell.h"
#include "../srcs/env_var/env_var.h"

void	action_failed(char *action) {}

int	main(int ac, char *av[])
{
	vars_append(&g_shell.vars, vars_new("TEMP", "VALUE_WOW"));
	return (munit_suite_main(&tokenizer_suite, NULL, ac, av));
}
