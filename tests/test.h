/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:14:11 by hunam             #+#    #+#             */
/*   Updated: 2023/06/23 19:34:24 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "munit/munit.h"

MunitResult	test_demo(const MunitParameter[], void *);

const MunitSuite	tokenizer_suite = {
	"/tokenizer",
	(MunitTest[]){
		{"/test_demo", test_demo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
		{NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}
	}, NULL, 1, MUNIT_SUITE_OPTION_NONE
};

#endif