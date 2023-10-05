/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 05:05:48 by ebennix           #+#    #+#             */
/*   Updated: 2023/10/04 22:39:52 by ebennix          ###   ########.fr       */
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
#include <stdbool.h>

#if !defined(OPEN_MAX)
#define OPEN_MAX 1024
#endif // OPEN_MAX

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif


int					ft_printchar(int fd, char c);
int					ft_printstr(int fd, char *c);
int					ft_printunsigned(int fd, int n);
int					ft_printnbr(int fd, int n);
int					ft_hex(int fd, int n, char flag);
int					ft_fprintf(int fd, const char *str, ...);

int					ft_isalpha(char c);

void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);

char				**free2d(char **str);
void				*ft_calloc(size_t nelem, size_t size);
char				**ft_split(char *str, char delim);
char				*ft_strdup(const char *s);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_atoi(const char *str);
char				*ft_strchr(const char *s, int c);

char				*ft_itoa(int n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

#endif