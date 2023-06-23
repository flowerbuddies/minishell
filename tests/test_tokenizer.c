/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:10:46 by hunam             #+#    #+#             */
/*   Updated: 2023/06/23 19:30:57 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "../srcs/tokenizer/tokenizer.h"

static void	tokenizer_one_test(char *line, t_type *types, char **datas, int len)
{
	t_tokenizer	tokenizer;
	t_token		*current;
	int			i;

	tokenizer.line = line;
	tokenize(&tokenizer);
	assert_false(tokenizer.errored);
	current = tokenizer.tokens;
	i = -1;
	while (++i < len && current)
	{
		assert_uint(current->type, ==, types[i]);
		if (datas[i])
			assert_string_equal(current->data, datas[i]);
		current = current->next;
	}
	assert_int(i, ==, len);
	list_free(tokenizer.tokens);
}

MunitResult	test_demo(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"| > \"abc\"'def'ghi >>",
		(t_type []){PIPE, SPACE, REDIR_OUT, SPACE, STRING, SPACE, REDIR_OUT_APPEND},
		(char *[]){ NULL, NULL,  NULL,      NULL,  "abcdefghi", NULL, NULL},
		7);
	return (MUNIT_OK);
}
