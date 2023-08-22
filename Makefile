# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/08/22 23:55:39 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := Minishell

ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall -Wextra
# -Werror 

HEADER := Mandatory/inc/minishell.h

FILES := Mandatory/minishell\
		 Mandatory/mini_parse/tokenizer\
		 Mandatory/mini_parse/get_tokens\
		 Mandatory/mini_parse/history\
		 Mandatory/utils/token_tools\
		 utils/ft_lstnew_env utils/ft_lstadd_back utils/ft_remove_node utils/ft_strcmp\
		 bin/ft_bultins bin/env bin/unset bin/cd bin/echo bin/pwd bin/exit bin/export\
		 utils/get_key utils/updates utils/ft_sort_list\

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

library:
	make -C lib

$(EXE) : $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(ARCH) -lreadline

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
