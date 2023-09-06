/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/06 04:18:57 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_defs.h"
# include "mini_structs.h"
# include <readline/history.h>
# include <readline/readline.h>

void				get_type(t_token *token, int moves);

int expand(t_mini_data *var);

int get_env(t_env **Henv, char **env);
char *get_val(char *line);

bool	linker(t_mini_data *var);

// void                ft_lstdoubly_cmds(t_command_table **head , t_command_table *node);
int					ft_iseparateur(char c);
int					ft_iswhite_space(char c);
void				ft_lstdoubly(t_token **head, t_token *node);

t_token				*get_tokens(char *prompt);
bool				tokenizer(t_mini_data *var);
bool				shell_history(t_mini_data *var, char *prompt);
void				get_type(t_token *token, int moves);

bool    group_args(t_mini_data *var);

char 	*get_key(char *line);
t_env	*ft_lstnew_env(char *key, char *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		ft_strcmp(char *s1, char *s2);
void 	ft_remove_node(t_env **begin_list, void *data_ref, int (*cmp)());
t_env 	*sort_list(t_env *lst, int (*cmp)(char *, char *));
char	*key_by_value(t_env *env, char *value);
char	*value_by_key(t_env *env, char *key);
t_env	*update_pwd(t_env *env, char *pwd);
t_env	*update_old_pwd(t_env *env, char *oldpwd);

//built-in functions:
int		ft_env(t_env *env);
int		mini_exit(char **av, t_env *env, int exit_status);
int		ft_bultin(char **arg, t_env *env);
void 	ft_unset(char **arg, t_env *env);
void	me_cd(char **av, t_env *env);
void	my_echo(char **av, t_env *env);
void	me_pwd(char **av, t_env *env);
void	export_it(char **av, t_env *env);

#endif
