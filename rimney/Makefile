# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 01:48:17 by rimney            #+#    #+#              #
#    Updated: 2022/12/27 22:54:50 by rimney           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d
LIBFTA = libft/libft.a
GNL_SRCS = Get_next_line/get_next_line.c \
			Get_next_line/get_next_line_utils.c \
		
MLX =  -framework OpenGL -framework AppKit
CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address 
SRCS = main.c \
		parsing/ft_parsing00.c \
		parsing/ft_parsing01.c \
		parsing/ft_parsing02.c \
		parsing/ft_parsing03.c \
		parsing/ft_parsing04.c \
		parsing/ft_parsing05.c \
		parsing/ft_parsing06.c \
		minilibx_opengl_20191021/libmlx.a \
	
all : $(LIBFTA)

$(LIBFTA) :
	(cd Libft && make)

all : $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(FLAGS) $(MLX) $(SRCS) $(GNL_SRCS) $(LIBFTA) -o $(NAME)
	
clean :
	(cd libft && make clean)
	rm -rf $(NAME)
fclean :
	(cd libft && make fclean)
	rm -rf $(NAME)
re : fclean all