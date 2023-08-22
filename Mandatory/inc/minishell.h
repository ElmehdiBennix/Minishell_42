/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/22 22:55:56 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include "../../lib/inc/utils.h"

typedef enum s_type
{
    WORD = 1,
	SINGLE_QUOT = 2,
	DOUBLE_QUOT = 3,
	PIPE = 4,
	GREAT = 5,
	LESS = 6,
	APPEND = 7, // >>
	HERE_DOC = 8, // <<

}	t_type;

typedef struct s_token
{
    int             id;
    char            *content;
    bool            space_after;
    t_type          type;
    struct s_token  *forward;
    struct s_token  *backward;
} t_token;

typedef struct s_mini_data
{
    int             err_no;
    char            **env_var;
	char	        **path_var;
    char            *PWD;
    char            *OLDPWD;
    struct s_token  *tokens;

}   t_mini_data;

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


# define TRUE 1
# define FALSE 0

void    get_type(t_token *token , int moves);

int ft_iseparateur(char c);
int ft_iswhite_space(char c);
void    ft_lstdoubly(t_token **head , t_token *node);

t_token *get_tokens(char *prompt);
void tokenizer(t_token *tokens);
bool shell_history(t_mini_data *var, char *prompt);
void    get_type(t_token *token , int moves);


#endif
