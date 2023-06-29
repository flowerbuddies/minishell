/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfm <mfm@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:33:39 by hunam             #+#    #+#             */
/*   Updated: 2023/06/29 17:22:43 by mfm              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"
#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	if (!init_env_vars(ev))
		return (1); // TODO: error
	print_vars(g_shell.vars); //TODO: remove when env_vars working properly
	prompt();
}
