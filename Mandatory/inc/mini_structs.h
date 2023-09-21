/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:48:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/21 04:11:19 by ebennix          ###   ########.fr       */
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
	GREAT = 5, // flags
	LESS = 6, // flags
	APPEND = 7,   // >>
	HERE_DOC = 8, // << 

}					t_type;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}           t_env;

typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

typedef struct s_token
{
	int				id;
	char			*content;
	bool			space_after;
	t_type			type;
	struct s_token	*forward;
	struct s_token	*backward;
}					t_token; 	// herdoc first == dup input < pipe or file_hiddenz

typedef struct s_redirection
{
	char 	*file_name;
	t_type	redirection;
	struct	s_redirection *next;   // ls > a > b > c create a next b till last then dup output only c is // read write flag--
}			t_redirection;

typedef struct s_command_table
{
	char 					**cmds_array;
	int 					fdin;
	int 					fdout;
	struct s_redirection	*redir;
	struct s_mini_data		*var;
	struct s_command_table	*forward;
	struct s_command_table	*backward;
}				t_command_table;

		typedef struct prototype
		{
			char				**content;
			t_type				type;
			int 				fdin;
			int 				fdout;
			int					shell_lev;
			struct prototype	*forward;
			struct prototype	*backward;
		}					_prototype;


typedef struct s_mini_data
{
	int						err_no;
	struct s_env			*env_var;
	int						nodes;
	int						shell_lev;
	struct s_token			*tokens;
	struct s_command_table	*exec_data;
}					t_mini_data;

// typedef struct	s_sig
// {
// 	int				sigint;
// 	int				sigquit;
// 	int				exit_status;
// 	pid_t			pid;
// }				t_sig;

// proto



#endif
