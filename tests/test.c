/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:31:53 by hunam             #+#    #+#             */
/*   Updated: 2023/06/23 19:19:48 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "test.h"

int	main(int ac, char *av[])
{
	return (munit_suite_main(&tokenizer_suite, NULL, ac, av));
}
