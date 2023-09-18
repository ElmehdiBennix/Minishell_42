# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/09/18 02:07:42 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := Minishell

ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall -Wextra 
# -Werror
# -fsanitize=address

HEADER := Mandatory/inc/minishell.h

FILES := Mandatory/minishell\
		 Mandatory/fake_struct\
		 Mandatory/parse/tokenizer\
		 Mandatory/parse/catch_tokens\
		 Mandatory/parse/history\
		 Mandatory/parse/expand\
		 Mandatory/parse/allocate_groups\
		 Mandatory/parse/linker\
		 Mandatory/parse/token_tools\
		 Mandatory/utils/ft_lstnew_env \
		 Mandatory/utils/ft_lstadd_back_env \
		 Mandatory/utils/ft_remove_node \
		 Mandatory/utils/ft_strcmp \
		 Mandatory/utils/get_back_env\
		 Mandatory/utils/get_key \
		 Mandatory/utils/updates \
		 Mandatory/utils/ft_sort_list \
		 Mandatory/bin/ft_bultins \
		 Mandatory/bin/env \
		 Mandatory/bin/unset \
		 Mandatory/bin/cd \
		 Mandatory/bin/echo \
		 Mandatory/bin/pwd \
		 Mandatory/bin/exit \
		 Mandatory/bin/export\
		 Mandatory/execution/exc \
		 Mandatory/execution/redirections \
		 Mandatory/execution/pipe_handler\

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
