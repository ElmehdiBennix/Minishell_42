/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/18 01:16:45 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_defs.h"
# include "mini_structs.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/uio.h>
# include <sys/wait.h>

void	get_type(t_token *token, int moves);

int		expand(t_mini_data *var);
bool	linker(t_mini_data *var);
// void                ft_lstdoubly_cmds(t_command_table **head ,t_command_table *node);
int		ft_iseparateur(char c);
int		ft_iswhite_space(char c);
void	ft_lstdoubly(t_token **head, t_token *node);

t_token	    *get_tokens(char *prompt);
bool	    tokenizer(t_mini_data *var);
bool	    shell_history(t_mini_data *var, char *prompt);
void	    get_type(t_token *token, int moves);
bool	    group_args(t_mini_data *var);
/// merge

_prototype	*fake_struct(char **cmds);
int		get_env(t_env **Henv, char **env);
char	*get_val(char *line);
char	*get_key(char *line);
t_env	*ft_lstnew_env(char *key, char *value);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		ft_strcmp(char *s1, char *s2);
void	ft_remove_node(t_env **begin_list, void *data_ref, int (*cmp)());
t_env	*sort_list(t_env *lst, int (*cmp)(char *, char *));
char	*key_by_value(t_env *env, char *value);
char	*value_by_key(t_env *env, char *key);
t_env	*update_pwd(t_env **env, char *pwd);
t_env	*update_old_pwd(t_env **env, char *oldpwd);
char	**get_normal_env(t_env *env);

//built-in functions:
int		ft_env(int fd, t_env *env);
int		mini_exit(char **av, t_env **env, int exit_status);
int		ft_bultin(_prototype *data, char **arg, t_env **env);
void	ft_unset(char **arg, t_env **env);
void	me_cd(char **av, t_env **env);
void	my_echo(_prototype *data, char **av, t_env **env);
void	me_pwd(int fd, char **av, t_env **env);
void	export_it(char **av, t_env **env);
int		is_bult_in(char *arg);
//exec functions:
void	one_cmd(_prototype **cmds, char **args, t_env **env);
void	exceute_it(_prototype **data, t_env **env);
int		red_open(int *fds, t_type red, char *f_name);
int		here_doc(int *fdin, char *str);
int		append(int *fdout, char *strout);
void	excute_one_cmd(_prototype **args, char **contents, t_env **env);
void	open_red(_prototype **data, char **cmds, t_env **env);
void	multi_cmd(_prototype **data, t_env **env);

#endif
