/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hunam <hunam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:56:31 by hunam             #+#    #+#             */
/*   Updated: 2023/09/14 16:23:45 by hunam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sig_interactive_mode(int signal);
void	sig_non_interactive_mode(int signal);
void	sig_heredoc_mode(int signal);

#endif