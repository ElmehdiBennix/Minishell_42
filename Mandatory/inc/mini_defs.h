/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_defs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:48:41 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/06 20:52:00 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_DEF_H
# define MINI_DEF_H

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// # define RED    "\x1b[1;31m"
// # define CYAN    "\x1b[1;36m"
// # define RESET    "\x1b[0m"

# define SYNX_0 "le minishell: this shell does not accept any arguments !!\n"
# define SYNX_1 "le minishell: syntax error near unexpected token `%c'\n"
# define SYNX_2 "le minishell: syntax error near unexpected token `newline'\n"
# define SYNX_3 "le minishell: syntax error `open quote'\n"
# define SYNX_4 "le minishell: syntax error near unexpected token `|'\n"
# define SYNX_5 "le minishell: fork: Resource temporarily unavailable \n"
# define SYNX_6 "le minishell: syntax error near unexpected token `%s'\n"

# define SUCCESS 0
# define ERROR 1

#endif