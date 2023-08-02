# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/08/02 11:48:19 by otaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := Minishell

ARCH := libft/libft.a

CC := cc 

CFLAGS := -g -Wall -Wextra -Werror 

HEADER := inc/minishell.h

FILES := minishell\
		utils/ft_lstnew_env utils/ft_lstadd_back utils/ft_remove_node utils/ft_strcmp\
		bin/ft_bultins bin/env bin/unset bin/cd\
		utils/get_key

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library:
	make -C libft

$(EXE) : $(OBJ)
	$(CC) -lreadline $(OBJ) $(ARCH) -o $(EXE)

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C libft
	$(RM) $(OBJ)

fclean : clean
	make fclean -C libft
	$(RM) $(EXE)

re : fclean all

git :
	git add .
	git status
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
