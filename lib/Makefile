# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 04:53:15 by ebennix           #+#    #+#              #
#    Updated: 2023/05/11 00:25:26 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := utils.a

CFLAGS := -g -Wall -Wextra -Werror

HEADER := /inc/utils.h
COLORS := /inc/colors.h

OBJ_DIR := obj_files

CC := cc

FILES := libft/string/ft_atoi		  libft/int/ft_itoa	               libft/int/ft_putnbr_fd	    \
		 libft/int/ft_strlcpy		  libft/char/ft_tolower	           libft/errors/exit_msg        \
		 libft/memory/ft_bzero	      libft/memory/ft_memchr	       libft/string/ft_putstr_fd	\
		 libft/int/ft_strlen	 	  libft/char/ft_toupper	           libft/errors/error   		\
		 libft/heap/ft_calloc	      libft/memory/ft_memcmp	       libft/heap/ft_split	     	\
		 libft/string/ft_strmapi	  libft/heap/ft_substr	           libft/lst/ft_lstcreate_front	\
		 libft/char/ft_isalnum	      libft/memory/ft_memcpy	       libft/string/ft_strchr	 	\
		 libft/int/ft_strncmp		  libft/lst/ft_lstclear	           get_next_line/get_next_line	\
		 libft/char/ft_isalpha	 	  libft/heap/ft_strdup	       	   libft/string/ft_strnstr		\
		 libft/char/ft_isascii	      libft/memory/ft_memset	       libft/string/ft_striteri		\
		 libft/string/ft_strrchr	  libft/string/ft_putendl_fd       fprintf/ft_fprintf  	 	  	\
		 libft/char/ft_isdigit	      libft/char/ft_putchar_fd	 	   libft/heap/ft_strjoin	 	\
		 libft/heap/ft_strtrim		  libft/int/ft_strlcat	           libft/lst/ft_lstcreate_back	\
		 libft/char/ft_isprint		  libft/memory/ft_memmove	 	   libft/lst/ft_lstsize	 	 	\
		 libft/lst/ft_lstadd_front	  libft/lst/ft_lstnew	  	       libft/lst/ft_lstlast      	\
		 libft/lst/ft_lstadd_back	  fprintf/utils/ft_fprintf_hex     fprintf/utils/ft_fprintf_put \
		 libft/heap/free2d

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
