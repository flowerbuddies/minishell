/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:14:11 by hunam             #+#    #+#             */
/*   Updated: 2023/06/26 15:27:56 by hunam            ###   ########.fr       */
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

const MunitSuite	tokenizer_suite = {
	"/tokenizer",
	(MunitTest[]){
		{"/test_demo", test_demo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_1", test_raw_string_1, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_2", test_raw_string_2, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_3", test_raw_string_3, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{"/test_raw_string_4", test_raw_string_4, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
	}, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

#endif