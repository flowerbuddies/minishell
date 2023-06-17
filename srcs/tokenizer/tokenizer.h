/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:06:27 by hunam             #+#    #+#             */
/*   Updated: 2023/06/17 13:25:16 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdbool.h>
# include <stdlib.h>

typedef enum e_type
{
	UNSET,
	COMMAND,
	RAW_STRING,
	STRING,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_OUT_APPEND,
	PIPE
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*data;
	struct s_token	*next;
}	t_token;

//linked_list.c
t_token	*list_new(void);
bool	list_append(t_token *tokens, t_type type, char *data);
t_token	*list_at(t_token *tokens, int idx);
void	list_free(t_token *tokens);

#endif