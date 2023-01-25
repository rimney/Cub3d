/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:00:33 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/24 22:50:37 by mrobaii          ###   ########.fr       */
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
	cube->stable->height = cube->mapheight * SCALE;
	cube->stable->width = cube->mapwidth * SCALE;
	cube->stable->num_of_rays = WINDOW_WIDTH;
}

void	ft_init_player(t_cube *cube)
{
	if (cube->psp == 'S')
		cube->player->angle = 180 * M_PI / 180;
	else if (cube->psp == 'N')
		cube->player->angle = 360 * M_PI / 180;
	else if (cube->psp == 'W')
		cube->player->angle = 270 * M_PI / 180;
	else
		cube->player->angle = 90 * M_PI / 180;
	cube->player->movespeed = 4;
	cube->player->rotationspeed = 4 * (M_PI / 180);
	cube->player->turndirection = 0;
	cube->player->walkdirection = 0;
	cube->p_position_x = cube->p_position_x * SCALE;
	cube->p_position_y = cube->p_position_y * SCALE;
}

void	ft_mlx_init(t_cube *cube)
{
	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, WINDOW_WIDTH, \
	WINDOW_HEIGHT, "Cub3D");
}

void	ft_struct_init(char **argv, t_cube *cube)
{
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_cf(cube, argv);
	ft_get_map(cube, argv);
	ft_img_init(cube->img);
	ft_init_player(cube);
	init_const_vr(cube);
	ft_mlx_init(cube);
	ft_textures_init(cube);
}
