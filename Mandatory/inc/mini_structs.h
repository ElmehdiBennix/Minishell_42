/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bennix <bennix@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:48:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/06 19:53:31 by bennix           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_STRUCTS_H
# define MINI_STRUCTS_H

# include "../../lib/inc/utils.h"

typedef enum s_type
{
	WORD = 1,
	SINGLE_QUOT = 2,
	DOUBLE_QUOT = 3,
	PIPE = 4,
	GREAT = 5,
	LESS = 6,
	APPEND = 7,
	HERE_DOC = 8,
}							t_type;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_expansions
{
	char					*new_arg;
	char					*buffer;
	int						i;
	int						j;
	int						f;
}							t_expansions;

typedef struct s_token
{
	char					*content;
	bool					space_after;
	t_type					type;
	struct s_token			*forward;
	struct s_token			*backward;
}							t_token;

typedef struct s_redirection
{
	t_type					r_type;
	char					*file_name;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command_table
{
	char					**cmds_array;
	int						fdin;
	int						fdout;
	struct s_redirection	*redirections;
	struct s_mini_data		*var;
	struct s_command_table	*forward;
	struct s_command_table	*backward;
}							t_command_table;

typedef struct s_mini_data
{
	int						err_no;
	struct s_env			*env_var;
	int						nodes;
	int						shell_lev;
	struct s_token			*tokens;
	struct s_command_table	*exec_data;
}							t_mini_data;

#endif
