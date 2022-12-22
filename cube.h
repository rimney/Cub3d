/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:45 by rimney            #+#    #+#             */
/*   Updated: 2022/12/22 21:01:33 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "Get_next_line/get_next_line.h"

typedef	struct	s_cube
{
    double		P_position_x;
    double		P_posotion_y;
    char	*NO; // 0
	char	*WE; // 2
	char	*EA; // 3
	char	*SO; // 1
	int		C; // 4
	int		F; // 5
	int		*files_f;
	int		Psp; // it contains the ascii value of the direction character
	int		MapHeight;
	int		MapWidth;
	char	**Map;
} t_cube;

/********************** Parsing Functions **********************/



#endif