# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebennix <ebennix@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 07:56:09 by ebennix           #+#    #+#              #
#    Updated: 2023/05/15 18:24:08 by ebennix          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXE := 

EXE_B := 

ARCH := utils/utils.a

CC := cc

CFLAGS := -Wall -Wextra -Werror

HEADER := 

HEADER := 

FILES := 

FILES_B := 

SRC := $(FILES:=.c)

OBJ := $(SRC:.c=.o)

SRC_B := $(FILES_B:=.c)

OBJ_B := $(SRC_B:.c=.o)

RM := rm -rf

m := MakefileAutoPush


all : $(EXE)

bonus : $(EXE_B)

library:
	make -C utils

$(EXE) : $(OBJ)
	$(CC) $(OBJ) $(ARCH) $(EXE)

$(EXE_B) : $(OBJ_B)
	$(CC) $(OBJ_B) $(ARCH) $(EXE_B)

%.o : %.c $(HEADER) $(HEADER_B) | library
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C utils
	$(RM) $(OBJ)
	$(RM) $(OBJ_B)

fclean : clean
	make fclean -C utils
	$(RM) $(EXE)
	$(RM) $(EXE_B)

re : fclean all

git :
	git add .
	git status
	git commit -m "$(m)"
	git push

.PHONY : all clean fclean re git play
