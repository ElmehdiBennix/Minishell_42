/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:12:28 by ebennix           #+#    #+#             */
/*   Updated: 2023/09/05 23:31:27 by otaraki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <string.h>
# include <fcntl.h>

#define BUFFER_SIZE 1

typedef enum s_type
{
	WORD = 1,
	SINGLE_QUOT = 2,
	DOUBLE_QUOT = 3,
	PIPE = 4,
	GREAT = 5,	  // >
	LESS = 6,     // <
	APPEND = 7,   // >>
	HERE_DOC = 8,
	BULT_IN = 9, // <<

}					t_type;

typedef struct s_token
{
	char			**content;
	// char			**red_files;
	t_type			type;
	bool			space_after;
	int 			fdin;
	int 			fdout;
	struct s_token	*forward;
	struct s_token	*backward;
}					t_token;


typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}					t_env;

t_token *fake_struct(char **cmds);
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
char	**get_normal_env(t_env *env);
//built-in functions:
int		ft_env(int  fd, t_env *env);
int		mini_exit(char **av, t_env **env, int exit_status);
int		ft_bultin(t_token *data, char **arg, t_env **env);
void 	ft_unset(char **arg, t_env **env);
void	me_cd(char **av, t_env **env);
void	my_echo(t_token *data, char **av, t_env **env);
void	me_pwd(int fd, char **av, t_env **env);
void	export_it(char **av, t_env **env);
void	exceute_it(t_token **data, t_env **env);
int		red_open(t_token **fds, t_type red, char *f_name);
int		here_doc(int *fdin, char *str);
int		append(int *fdout, char *strout);
char	*get_next_line(int fd);

// void tokeni(char *f_line);

#endif
