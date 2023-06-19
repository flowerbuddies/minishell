/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:06:27 by hunam             #+#    #+#             */
/*   Updated: 2023/06/19 18:30:38 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdbool.h>

typedef enum e_type
{
	UNSET,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	SPACE,
	PIPE,
	STRING,
	ENV_VAR,
}	t_type;

typedef enum e_state
{
	IN_DEFAULT,
	IN_RAW_STRING,
	IN_STRING,
	IN_ENV_VAR,
	IN_COMMAND
}	t_state;

typedef struct s_token
{
	t_type			type;
	char			*data;
	struct s_token	*next;
}	t_token;

typedef struct s_tokenizer
{
	t_token		*tokens;
	const char	*line;
	int			i;
	t_state		state;
	int			str_start_idx;
	int			env_start_idx;
}	t_tokenizer;

//linked_list.c
t_token	*list_new(void);
bool	list_append(t_token *tokens, t_type type, char *data);
t_token	*list_at(t_token *tokens, int idx);
void	list_free(t_token *tokens);
void	list_print(t_token *tokens);

//tokenizer.c
t_token	*tokenize(const char *line);

//states.c
t_state	default_state(t_tokenizer *tokenizer, int i);
t_state	in_command_state(t_tokenizer *tokenizer, int i);
t_state	in_raw_string_state(t_tokenizer *tokenizer, int i);
t_state	in_string_state(t_tokenizer *tokenizer, int i);
t_state	in_env_var_state(t_tokenizer *tokenizer, int i);

#endif
