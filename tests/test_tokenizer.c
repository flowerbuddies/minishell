/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:10:46 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 17:23:28 by mfm              ###   ########.fr       */
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

MunitResult	test_redir1(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		">",
		(t_type []){REDIR_OUT},
		(char *[]){NULL},
		1);
	return (MUNIT_OK);
}

MunitResult	test_redir2(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"> > ",
		(t_type []){REDIR_OUT, SPACE, REDIR_OUT, SPACE},
		(char *[]){NULL, NULL, NULL, NULL},
		4);
	return (MUNIT_OK);
}

MunitResult	test_redir3(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"  >   >   >",
		(t_type []){SPACE, REDIR_OUT, SPACE, REDIR_OUT, SPACE, REDIR_OUT},
		(char *[]){NULL, NULL, NULL, NULL, NULL, NULL},
		6);
	return (MUNIT_OK);
}

MunitResult	test_redir4(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		">>",
		(t_type []){REDIR_OUT_APPEND},
		(char *[]){NULL},
		1);
	return (MUNIT_OK);
}

MunitResult	test_redir5(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"<",
		(t_type []){REDIR_IN},
		(char *[]){NULL},
		1);
	return (MUNIT_OK);
}

MunitResult	test_redir6(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"< <",
		(t_type []){REDIR_IN, SPACE, REDIR_IN},
		(char *[]){NULL, NULL, NULL},
		3);
	return (MUNIT_OK);
}

MunitResult	test_redir7(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"<<",
		(t_type []){HEREDOC},
		(char *[]){NULL},
		1);
	return (MUNIT_OK);
}

MunitResult	test_redir8(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"<< <<",
		(t_type []){HEREDOC, SPACE, HEREDOC},
		(char *[]){NULL, NULL, NULL},
		3);
	return (MUNIT_OK);
}

MunitResult	test_redir_mixed1(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		">> >",
		(t_type []){REDIR_OUT_APPEND, SPACE, REDIR_OUT},
		(char *[]){NULL, NULL, NULL},
		3);
	return (MUNIT_OK);
}

MunitResult	test_redir_mixed2(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		">> > >>",
		(t_type []){REDIR_OUT_APPEND, SPACE, REDIR_OUT, SPACE, REDIR_OUT_APPEND},
		(char *[]){NULL, NULL, NULL, NULL, NULL},
		5);
	return (MUNIT_OK);
}

MunitResult	test_redir_mixed3(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		">> > < <<",
		(t_type []){REDIR_OUT_APPEND, SPACE, REDIR_OUT, SPACE, REDIR_IN, SPACE, HEREDOC},
		(char *[]){NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		7);
	return (MUNIT_OK);
}

MunitResult	test_redir_mixed4(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"< << >> >",
		(t_type []){REDIR_IN, SPACE, HEREDOC, SPACE, REDIR_OUT_APPEND, SPACE, REDIR_OUT},
		(char *[]){NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		7);
	return (MUNIT_OK);
}

MunitResult	test_redir_mixed5(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"<< < > >>",
		(t_type []){HEREDOC, SPACE, REDIR_IN, SPACE, REDIR_OUT, SPACE, REDIR_OUT_APPEND},
		(char *[]){NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		7);
	return (MUNIT_OK);
}

MunitResult	test_redir_mixed6(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"< >> << >",
		(t_type []){REDIR_IN, SPACE, REDIR_OUT_APPEND, SPACE, HEREDOC, SPACE, REDIR_OUT},
		(char *[]){NULL, NULL, NULL, NULL, NULL, NULL, NULL},
		7);
	return (MUNIT_OK);
}

MunitResult	test_raw_string_1(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"'a'",
		(t_type []){STRING},
		(char *[]){"a"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_raw_string_2(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"'abc'",
		(t_type []){STRING},
		(char *[]){"abc"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_raw_string_3(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"'abc''def'",
		(t_type []){STRING},
		(char *[]){"abcdef"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_raw_string_4(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"| 'abc'>'def'",
		(t_type []){PIPE, SPACE, STRING, REDIR_OUT, STRING},
		(char *[]){NULL, NULL,   "abc", NULL,       "def"},
		5);
	return (MUNIT_OK);
}

MunitResult	test_string_1(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"\"a\"",
		(t_type []){STRING},
		(char *[]){"a"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_string_2(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"\"abc\"",
		(t_type []){STRING},
		(char *[]){"abc"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_string_3(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"\"abc\"\"def\"",
		(t_type []){STRING},
		(char *[]){"abcdef"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_string_4(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"| \"abc\">\"def\"",
		(t_type []){PIPE, SPACE, STRING, REDIR_OUT, STRING},
		(char *[]){NULL, NULL,   "abc", NULL,       "def"},
		5);
	return (MUNIT_OK);
}

MunitResult	test_string_5(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"\"abc\"'def'>",
		(t_type []){STRING, REDIR_OUT},
		(char *[]){"abcdef", NULL},
		2);
	return (MUNIT_OK);
}

MunitResult	test_command_1(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"a",
		(t_type []){STRING},
		(char *[]){"a"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_command_2(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"abc",
		(t_type []){STRING},
		(char *[]){"abc"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_command_3(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"abc\"def\"'ghi'",
		(t_type []){STRING},
		(char *[]){"abcdefghi"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_command_4(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"| abc>def",
		(t_type []){PIPE, SPACE, STRING, REDIR_OUT, STRING},
		(char *[]){NULL, NULL,   "abc", NULL,       "def"},
		5);
	return (MUNIT_OK);
}

MunitResult	test_command_5(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"string|",
		(t_type []){STRING, PIPE},
		(char *[]){"string", NULL},
		2);
	return (MUNIT_OK);
}

MunitResult	test_command_6(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"str1|str2",
		(t_type []){STRING, PIPE, STRING},
		(char *[]){"str1", NULL, "str2"},
		3);
	return (MUNIT_OK);
}

MunitResult	test_command_7(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"str1''",
		(t_type []){STRING},
		(char *[]){"str1"},
		1);
	return (MUNIT_OK);
}

MunitResult	test_command_8(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"str1\"\"",
		(t_type []){STRING},
		(char *[]){"str1"},
		1);
	return (MUNIT_OK);
}

MunitResult test_pipe_1(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"|",
		(t_type []){PIPE},
		(char *[]){NULL},
		1);
	return (MUNIT_OK);
}

MunitResult test_pipe_2(const MunitParameter params[], void *user_data_or_fixture)
{
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		" | ",
		(t_type []){SPACE, PIPE, SPACE},
		(char *[]){NULL, NULL, NULL},
		3);
	return (MUNIT_OK);
}

MunitResult test_pipe_3(const MunitParameter params[], void *user_data_or_fixture)
{
	return (MUNIT_SKIP);
	(void) params;
	(void) user_data_or_fixture;
	tokenizer_one_test(
		"abc|",
		(t_type []){STRING, PIPE},
		(char *[]){NULL, NULL},
		2);
	return (MUNIT_OK);
}
