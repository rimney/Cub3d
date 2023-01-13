/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:00:33 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/13 03:01:18 by mrobaii          ###   ########.fr       */
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

void ft_init_player(t_player *player)
{
	player->angle = M_PI / 2;
	player->movespeed = 2;
	player->rotationspeed = 2 * 3.1415926535 / 180;
	player->turndirection = 0;
	player->walkdirection = 0;	
}

void ft_mlx_init(t_cube *cube)
{
	cube->mlx_init = mlx_init();
	cube->img->img = mlx_new_image(cube->mlx_init, cube->MapWidth * SCALE, cube->MapWidth * SCALE);
	cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, &cube->img->size_len, &cube->img->endian);
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE, "Cub3D");
}

void	ft_struct_init(char **argv, t_cube *cube)
{
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	ft_img_init(cube->img);
	ft_init_player(cube->player);
	ft_mlx_init(cube);
}