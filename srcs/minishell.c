/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/07/08 00:15:09 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"
#include "executor.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

void	action_failed(char *action)
{
	printf("\e[31;1mError\e[0m: \e[4m%s\e[0m failed. %s\n", action, strerror(errno));
	exit(1);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	init_env_vars(ev);
	prompt();
}
