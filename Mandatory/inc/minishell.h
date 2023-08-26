/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/08/26 19:48:51 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"


typedef struct s_token
{
    int             flag_s;
    char            *content;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;


typedef struct s_lex
{
	char            *str;
	int             i;
    t_token         *token;
	struct s_lex	*next;
	struct s_lex	*prev;
}	t_lex;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;

}t_env;

int		get_env(t_env **Henv, char **env);
char 	*get_val(char *line);
char 	*get_key(char *line);
t_env	*ft_lstnew_env(char *key, char *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		ft_strcmp(char *s1, char *s2);
void 	ft_remove_node(t_env **begin_list, void *data_ref, int (*cmp)());
t_env 	*sort_list(t_env *lst, int (*cmp)(char *, char *));
char	*key_by_value(t_env *env, char *value);
char	*value_by_key(t_env *env, char *key);
t_env	*update_pwd(t_env **env, char *pwd);
t_env	*update_old_pwd(t_env **env, char *oldpwd);
//built-in functions:
int		ft_env(t_env *env);
int		mini_exit(char **av, t_env **env, int exit_status);
int		ft_bultin(char **arg, t_env **env);
void 	ft_unset(char **arg, t_env **env);
void	me_cd(char **av, t_env **env);
void	my_echo(char **av, t_env **env);
void	me_pwd(char **av, t_env **env);
void	export_it(char **av, t_env **env);

// void tokeni(char *f_line);

#endif
