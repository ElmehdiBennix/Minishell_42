# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 04:53:15 by ebennix           #+#    #+#              #
#    Updated: 2023/10/04 22:45:34 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := lib_42.a

CFLAGS := -Wall -Werror -Wextra

CC := cc

HEADER := /inc/utils.h
COLORS := /inc/colors.h

OBJ_DIR := obj_files

FILES := libft/int/ft_atoi  	\
		 libft/string/ft_itoa	\
		 libft/int/ft_strlcpy	\
		 libft/memory/ft_bzero	 \
		 libft/int/ft_strlen	  \
		 libft/heap/ft_calloc	   \
		 libft/heap/ft_split	 	\
	     libft/memory/ft_memcpy	    \
		 libft/string/ft_strchr	 	\
		 libft/int/ft_strncmp		 \
		 libft/int/ft_isalpha	 	 \
		 libft/heap/ft_strdup	     \
		 libft/memory/ft_memset	     \
		 libft/heap/ft_strjoin	 	  \
		 libft/heap/ft_strtrim		  \
		 libft/heap/free2d             \
		 fprintf/ft_fprintf  	fprintf/utils/ft_fprintf_hex     fprintf/utils/ft_fprintf_put\

SRC := $(FILES:=.c)
OBJ := $(SRC:.c=.o)

AR := ar -rc
RM := rm -rf


all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o:%.c $(HEADER) $(COLORS)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean
