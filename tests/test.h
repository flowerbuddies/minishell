/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:14:11 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 17:24:02 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "munit/munit.h"

MunitResult	test_demo(const MunitParameter[], void *);

MunitResult	test_raw_string_1(const MunitParameter[], void *);
MunitResult	test_raw_string_2(const MunitParameter[], void *);
MunitResult	test_raw_string_3(const MunitParameter[], void *);
MunitResult	test_raw_string_4(const MunitParameter[], void *);

MunitResult	test_redir1(const MunitParameter[], void *);
MunitResult	test_redir2(const MunitParameter[], void *);
MunitResult	test_redir3(const MunitParameter[], void *);
MunitResult	test_redir4(const MunitParameter[], void *);
MunitResult	test_redir5(const MunitParameter[], void *);
MunitResult	test_redir6(const MunitParameter[], void *);
MunitResult	test_redir7(const MunitParameter[], void *);
MunitResult	test_redir8(const MunitParameter[], void *);
MunitResult	test_redir_mixed1(const MunitParameter[], void *);
MunitResult	test_redir_mixed2(const MunitParameter[], void *);
MunitResult	test_redir_mixed3(const MunitParameter[], void *);
MunitResult	test_redir_mixed4(const MunitParameter[], void *);
MunitResult	test_redir_mixed5(const MunitParameter[], void *);
MunitResult	test_redir_mixed6(const MunitParameter[], void *);

MunitResult	test_string_1(const MunitParameter[], void *);
MunitResult	test_string_2(const MunitParameter[], void *);
MunitResult	test_string_3(const MunitParameter[], void *);
MunitResult	test_string_4(const MunitParameter[], void *);
MunitResult	test_string_5(const MunitParameter[], void *);

MunitResult	test_command_1(const MunitParameter[], void *);
MunitResult	test_command_2(const MunitParameter[], void *);
MunitResult	test_command_3(const MunitParameter[], void *);
MunitResult	test_command_4(const MunitParameter[], void *);
MunitResult	test_command_5(const MunitParameter[], void *);
MunitResult	test_command_6(const MunitParameter[], void *);
MunitResult	test_command_7(const MunitParameter[], void *);
MunitResult	test_command_8(const MunitParameter[], void *);

MunitResult	test_pipe_1(const MunitParameter[], void *);
MunitResult	test_pipe_2(const MunitParameter[], void *);
MunitResult	test_pipe_3(const MunitParameter[], void *);

const MunitSuite	tokenizer_suite = {
	"/tokenizer",
	(MunitTest[]){
		{"/test_demo", test_demo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_1", test_raw_string_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_2", test_raw_string_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_3", test_raw_string_3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_4", test_raw_string_4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

		{"/test_redir1", test_redir1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir2", test_redir2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir3", test_redir3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir4", test_redir4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir5", test_redir5, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir6", test_redir6, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir7", test_redir7, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir8", test_redir8, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir_mixed1", test_redir_mixed1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir_mixed2", test_redir_mixed2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir_mixed3", test_redir_mixed3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir_mixed4", test_redir_mixed4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir_mixed5", test_redir_mixed5, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_redir_mixed6", test_redir_mixed6, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

		{"/test_string_1", test_string_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_string_2", test_string_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_string_3", test_string_3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_string_4", test_string_4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_string_5", test_string_5, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

		{"/test_command_1", test_command_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_2", test_command_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_3", test_command_3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_4", test_command_4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_5", test_command_5, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_6", test_command_6, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_7", test_command_7, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_command_8", test_command_8, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},

		{"/test_pipe_1", test_pipe_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_pipe_2", test_pipe_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_pipe_3", test_pipe_3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
	}, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

#endif
