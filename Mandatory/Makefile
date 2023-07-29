# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/07/24 02:36:50 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := Minishell

# ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall -Wextra 
# -Werror 

HEADER := inc/minishell.h

FILES := minishell ft_lstnew_env ft_lstadd_back\

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)



$(EXE) : $(OBJ)
	$(CC) -lreadline $(OBJ) $(ARCH) -o $(EXE)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean 
	$(RM) $(OBJ)

fclean : clean
	make fclean 
	$(RM) $(EXE)

re : fclean all

git :
	git add .
	git status
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
