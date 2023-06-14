/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 05:05:48 by ebennix           #+#    #+#             */
/*   Updated: 2023/05/09 21:14:23 by ebennix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "colors.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// # define NULL (void *)0

int					ft_printchar(int fd, char c);
int					ft_printstr(int fd, char *c);
int					ft_printunsigned(int fd, unsigned int n);
int					ft_printnbr(int fd, int n);
int					ft_hex(int fd, unsigned int n, char flag);
int					ft_fprintf(int fd, const char *str, ...);

void				failure(int erno);
void				exit_msg(int fd, char *msg, char *color, int erno);

char				*get_next_line(int fd);
void				ft_lstfree(void *stack);

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
void				*ft_calloc(size_t nelem, size_t size);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(char c);
int					ft_isalpha(char c);
int					ft_isascii(char c);
int					ft_isdigit(char c);
int					ft_isprint(char c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char *str, char delim);
char				**free2d(char **str);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char *s1, char *s2);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(char c);
int					ft_toupper(char c);
int					ft_lstsize(t_list *lst);
void				ft_lstcreate_front(t_list **lst, void *content);
void				ft_lstcreate_back(t_list **lst, void *content);
void				ft_lstadd_front(t_list **lst, t_list *new_node);
void				ft_lstadd_back(t_list **lst, t_list *new_node);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);

#endif