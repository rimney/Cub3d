# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney <rimney@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 01:48:17 by rimney            #+#    #+#              #
#    Updated: 2022/12/20 03:15:00 by rimney           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d
LIBFTA = Libft/libft.a
GNL_SRCS = Get_next_line/get_next_line.c \
			Get_next_line/get_next_line_utils.c \

CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
SRCS = parsing.c


all : $(LIBFTA)

$(LIBFTA) :
	(cd Libft && make)

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(SRCS) $(GNL_SRCS) $(LIBFTA) -o $(NAME)
	
	