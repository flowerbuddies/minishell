/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:31:53 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 15:37:16 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "test.h"
#include "../srcs/minishell.h"
#include "../libft/libft.h"
#include "../srcs/env_var/env_var.h"

void	action_failed(char *action) {
	(void) action;
}

bool	streq(const char *s1, const char *s2)
{
	const int	s1_len = ft_strlen(s1);

	return (s1_len == (int)ft_strlen(s2) && ft_strncmp(s1, s2, s1_len) == 0);
}

int	main(int ac, char *av[])
{
	vars_append(&get_shell()->vars, vars_new("TEMP", "VALUE_WOW"));
	return (munit_suite_main(&tokenizer_suite, NULL, ac, av));
}
