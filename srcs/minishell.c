/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/07/01 00:17:28 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"

void	malloc_failed(void)
{
	ft_printf("\e[31;1mError\e[0m: \e[4mmalloc\e[0m failed\n");
	exit(1);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	init_env_vars(ev);
	print_vars(g_shell.vars); //TODO: rm
	prompt();
}
