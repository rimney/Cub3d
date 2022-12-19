/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:45 by rimney            #+#    #+#             */
/*   Updated: 2022/12/19 20:02:18 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "Libft/libft.h"
#include "Get_next_line/get_next_line.h"

typedef	struct	s_cube
{
    int		P_position_x;
    int		P_posotion_y;
    char	*NO; // 0
	char	*WE; // 2
	char	*EA; // 3
	char	*SO; // 1
	int		C; // 4
	int		F; // 5
	int		*files_f;
	int		MapHeight;
} t_cube;

/********************** Parsing Functions **********************/



#endif