/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmulle <marmulle@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:40:20 by hunam             #+#    #+#             */
/*   Updated: 2023/09/12 19:50:55 by marmulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

int	len2d(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	free2d(char **array)
{
	int	len;

	if (!array)
		return ;
	len = 0;
	while (array[len])
		if (array[len])
			free(array[len++]);
	if (array)
		free(array);
}
