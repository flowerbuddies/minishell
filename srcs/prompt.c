/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:11:44 by hunam             #+#    #+#             */
/*   Updated: 2023/06/15 20:07:46 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	prompt(void)
{
	char	*line;

	while (42)
	{
		line = readline("MiniHell $ ");
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			exit(0);
		}
		if (line[0])
			add_history(line);
		free(line);
	}
}
