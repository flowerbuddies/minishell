/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:23:44 by hunam             #+#    #+#             */
/*   Updated: 2023/07/02 20:09:17 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <stdio.h> //TODO: rm
#include <unistd.h>
#include <stdlib.h> //TODO: rm
#include <errno.h> //TODO: rm
#include "libft.h" //TODO: rm

void	execute(t_node *ast)
{
	// if (ast->type == PIPE)
	// {
	// 	execute(ast->left);
	// 	execute(ast->right);
	// }
	// if (ast->type == STRING)
	// 	printf("->%s\n", ast->data->data);
	int child_pid = fork();
	execve("/usr/bin/uname", (char *[]){"uname", "-a", NULL}, NULL);
}

