/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/05 23:33:58 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_defs.h"
# include "mini_structs.h" // headers inc
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/uio.h>
# include <sys/wait.h>


int	    single_key(int c);
int	    multi_key(int c);
int		ft_iseparateur(char c);
int		ft_iswhite_space(char c);
t_type	get_type(char *token, int moves);

char    *join_it(char *s1, char *s2, int flag);
bool	toks_doubly(t_token **head, t_token *node);
bool	cmds_doubly(t_command_table **head, t_command_table *node);

char	*get_value(char *content, t_mini_data *var);

bool	last_index(char *prompt);
bool	first_index(char *prompt);
bool	skip_space_history(char *prompt);

//parse functions
bool	shell_history(t_mini_data *var, char *prompt);
bool	token_catcher(char *prompt, t_mini_data *var);
bool	parser(t_mini_data *var);
bool	expander(t_mini_data *var);
bool	allocate_groups(t_mini_data *var);
bool	linker(t_mini_data *var);

/// merge

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
char	*get_key_plus(char *line);
t_env	*update_env(t_env **env, char *value, char *key);
char	**get_normal_env(t_env *env);

//built-in functions:
int		ft_env(int fd, char **av, t_env *env);
int		mini_exit(char **av, int exit_status);
int		ft_bultin(t_command_table *data, t_env **env);
void	ft_unset(char **arg, t_env **env);
void	me_cd(char **av, t_env **env);
void	my_echo(char **av);
void	me_pwd(int fd, t_env **env);
void	export_it(char **av, t_env **env);
int		is_bult_in(char *arg);

//exec functions:
int		one_cmd(t_command_table *exec_data, t_env **env);
int		red_open(int *fds, t_type red, char *f_name);
int		here_doc(int *fdin, char *str, char **f_name, t_mini_data *var);
int		excute_one_cmd(char **contents, t_env **env);
int		open_red(t_command_table *exec_data);
int		multi_cmd(t_command_table *exec_data, t_env **env);

//free functions
void	tok_free(t_token *node, bool free_content);
void	cmd_free(t_command_table *node, bool free_content);
void	red_free(t_redirection *node, bool free_content);
void	unlink_opened_files(void);

#endif
