# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otaraki <otaraki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/07/24 00:07:27 by otaraki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := Minishell

ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall -Wextra -Werror 

HEADER := Mandatory/inc/minishell.h

FILES := Mandatory/minishell\
		 Mandatory/lexer/tokenizer\
		 Mandatory/lexer/valid_cmd\

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library:
	make -C lib

$(EXE) : $(OBJ)
	$(CC) -lreadline $(OBJ) $(ARCH) -o $(EXE)

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C lib
	$(RM) $(OBJ)

fclean : clean
	make fclean -C lib
	$(RM) $(EXE)

re : fclean all

git :
	git add .
	git status
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
