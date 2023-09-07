/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:44:16 by hunam             #+#    #+#             */
/*   Updated: 2023/07/19 18:26:16 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdbool.h>

typedef enum e_type
{
	_NOT_SET,
	REDIR_IN,
	HEREDOC,
	REDIR_OUT,
	REDIR_OUT_APPEND,
	SPC,
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
	char		*line;
	int			i;
	t_state		state;
	int			str_start_idx;
	int			env_start_idx;
	bool		errored;
}	t_tokenizer;

// linked_list/setter.c
t_token	*tokens_new(t_tokenizer *tokenizer);
void	tokens_append(t_tokenizer *tokenizer, t_type type, char *data);
void	tokens_delete_at(t_tokenizer *tokenizer, int idx);
void	tokens_free(t_token *tokens);

// linked_list/getter.c
t_token	*tokens_at(t_token *tokens, int idx);
void	tokens_print(t_token *tokens);

// tokenizer.c
void	tokenize(t_tokenizer *tokenizer);

// post_process/*
void	evaluate_env_vars(t_tokenizer *tokenizer);
void	concat_string_tokens(t_tokenizer *tokenizer);
void	delete_space_tokens(t_tokenizer *tokenizer);
void	heredocs_prompt_user_input(t_tokenizer *tokenizer);
void	single_sided_redirs(t_tokenizer *tokenizer);

// states/*
t_state	in_default_state(t_tokenizer *tokenizer, int i);
t_state	in_command_state(t_tokenizer *tokenizer, int i);
t_state	in_raw_string_state(t_tokenizer *tokenizer, int i);
t_state	in_string_state(t_tokenizer *tokenizer, int i);
t_state	in_env_var_state(t_tokenizer *tokenizer, int i);

#endif
