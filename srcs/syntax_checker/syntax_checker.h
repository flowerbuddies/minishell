/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:13:01 by hunam             #+#    #+#             */
/*   Updated: 2023/07/01 01:43:49 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_CHECKER_H
# define SYNTAX_CHECKER_H

# include <stdbool.h>
# include "tokenizer.h"

//syntax_checker.c
bool	check_syntax(t_tokenizer *tokenizer);

#endif