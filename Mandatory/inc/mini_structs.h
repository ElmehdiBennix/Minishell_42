/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 23:48:21 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/29 23:06:36 by ebennix          ###   ########.fr       */
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
	APPEND = 7,   // >>
	HERE_DOC = 8, // <<

}					t_type;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;

}           t_env;

typedef struct s_token
{
	int				id;
	char			*content;
	bool			space_after;
	t_type			type;
	struct s_token	*forward;
	struct s_token	*backward;
}					t_token;

typedef struct s_mini_data
{
	int				err_no;
	// char			**env_var;
	struct s_env	*env_var;
	char			**path_var;
	char			*PWD;
	char			*OLD_PWD;
	struct s_token	*tokens;

}					t_mini_data;


// typedef struct	s_sig
// {
// 	int				sigint;
// 	int				sigquit;
// 	int				exit_status;
// 	pid_t			pid;
// }				t_sig;

typedef struct	s_expansions
{
	char			*new_arg;
	int				i;
	int				j;
}				t_expansions;

// typedef      //pipe split commands
// {
//     char    **command;
//     // int     ;
//     // int     ;
//     // int     ;
//     struct   *forward;
//     struct   *backward;
// }

//char ** // split pipe with herdog
// pointer foraw
// back
// each node has a **pointer next means pipe

#endif
