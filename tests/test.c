/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:31:53 by hunam             #+#    #+#             */
/*   Updated: 2023/06/29 23:19:01 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "test.h"
#include "../srcs/minishell.h"
#include "../srcs/env_var/env_var.h"

int	main(int ac, char *av[])
{
	vars_append(&g_shell.vars, new_var("TEMP", "VALUE_WOW"));
	return (munit_suite_main(&tokenizer_suite, NULL, ac, av));
}
