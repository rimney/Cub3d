/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:00:33 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/19 23:14:17 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_img_init(t_img *img)
{
	img->bpp = 0;
	img->endian = 0;
	img->size_len = 0;
	img->addr = NULL;
}

void	init_const_vr(t_cube *cube)
{
	cube->stable->fov = 60 * (M_PI / 180);
	cube->stable->height = cube->MapHeight * SCALE;
	cube->stable->width = cube->MapWidth * SCALE;
	cube->stable->num_of_rays = cube->stable->width;
}

void ft_init_player(t_cube *cube)
{
	if (cube->Psp == 'S')
		cube->player->angle = 180 * M_PI / 180;
	else if (cube->Psp == 'N')
		cube->player->angle = 360 * M_PI / 180;
	else if (cube->Psp == 'W')
		cube->player->angle = 270 * M_PI / 180;
	else
		cube->player->angle = 90 * M_PI / 180;
	cube->player->movespeed = 5;
	cube->player->rotationspeed = 5 * (M_PI / 180);
	cube->player->turndirection = 0;
	cube->player->walkdirection = 0;
	cube->P_position_x = cube->P_position_x * SCALE;
	cube->P_position_y = cube->P_position_y * SCALE;
}

void ft_mlx_init(t_cube *cube)
{
	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->stable->width, cube->stable->height, "Cub3D");
}

void	ft_struct_init(char **argv, t_cube *cube)
{
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	ft_img_init(cube->img);
	ft_init_player(cube);
	init_const_vr(cube);
	ft_mlx_init(cube);
}
