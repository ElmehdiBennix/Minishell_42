# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/10/05 23:34:24 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := Minishell

ARCH := lib/lib_42.a

CC := cc 

CFLAGS := -g -Wall  -Wextra
#-fsanitize=address 

HEADER := Mandatory/inc/minishell.h

FILES := Mandatory/minishell\
		 Mandatory/parse/parser\
		 Mandatory/parse/token_catcher\
		 Mandatory/parse/history\
		 Mandatory/parse/expand\
		 Mandatory/parse/history_tools\
		 Mandatory/parse/allocate_groups\
		 Mandatory/parse/linker\
		 Mandatory/parse/checks_tools\
		 Mandatory/parse/lst_tools\
		 Mandatory/utils/ft_lstnew_env \
		 Mandatory/utils/ft_lstadd_back_env \
		 Mandatory/utils/ft_remove_node \
		 Mandatory/utils/ft_strcmp \
		 Mandatory/utils/get_back_env\
		 Mandatory/utils/get_key \
		 Mandatory/utils/updates \
		 Mandatory/utils/reset_structs \
		 Mandatory/utils/ft_sort_list \
		 Mandatory/bin/ft_bultins \
		 Mandatory/bin/env\
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

USER := $(shell whoami)

LDFLAGS := "-L/Users/$(USER)/homebrew/opt/readline/lib"

CPPFLAGS := "-I/Users/$(USER)/homebrew/opt/readline/include"

VAR := $(CPPFLAGS) $(LDFLAGS)

all : $(EXE)

library:
	make -C lib

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $(VAR) $(OBJ) $(ARCH) -o $(EXE) -lreadline

%.o : %.c $(HEADER) | library
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean :
	make clean -C lib
	$(RM) $(OBJ)

fclean : clean
	make fclean -C lib
	$(RM) $(EXE)

re : fclean all

git :
	make fclean
	git add .
	git status
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git
