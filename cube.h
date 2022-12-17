/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:45 by rimney            #+#    #+#             */
/*   Updated: 2022/12/17 01:58:51 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>


typedef	struct	s_cube
{
    int		P_position_x;
    int		P_posotion_y;
    char	*NO;
	char	*WE;
	char	*EA;
	char	*SO;
	int		MapHeight;
} t_cube;

/********************** Parsing Functions **********************/



#endif