/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:13:39 by marmulle          #+#    #+#             */
/*   Updated: 2023/07/06 19:10:33 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*decode_string(int read_end)
{
	char	*string;
	int		string_len;

	if (read(read_end, &string_len, sizeof(int)) == -1)
		action_failed("read");
	string = malloc(sizeof(char) * (string_len + 1));
	if (!string)
		action_failed("malloc");
	if (read(read_end, string, string_len) == -1)
		action_failed("read");
	string[string_len] = '\0';
	return (string);
}

char	**decode_array(int read_end)
{
	char	**array;
	int		array_len;
	int		elem_len;
	int		i;

	if (read(read_end, &array_len, sizeof(int)) == -1)
		action_failed("read");
	array = malloc(sizeof(char *) * (array_len + 1));
	if (!array)
		action_failed("malloc");
	array[array_len] = NULL;
	i = -1;
	while (++i < array_len)
	{
		if (read(read_end, &elem_len, sizeof(int)) == -1)
			action_failed("read");
		array[i] = malloc(sizeof(char) * (elem_len + 1));
		if (!array[i])
			action_failed("malloc");
		if (read(read_end, array[i], elem_len) == -1)
			action_failed("read");
		array[i][elem_len] = '\0';
	}
	return (array);
}
