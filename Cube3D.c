/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:03:45 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/25 02:40:57 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_a_wall(int x, int y, t_cube *cube)
{
	if (x < 0 || x > cube->stable->width || y < 0 || y > cube->stable->height)
		return (1);
	if ((size_t)x < ft_strlen(cube->map[y]) && cube->map[y][x] == '1')
		return (1);
	return (0);
}

int	cub_draw(t_cube *cube)
{
	ft_new_image(cube);
	update_player(cube);
	floor_ceeling_render(cube);
	cast_all_ray(cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, \
	cube->img->img, 0, 0);
	mlx_destroy_image(cube->mlx_init, cube->img->img);
	return (0);
}

void	update_player(t_cube *cube)
{
	double	movestep;
	double	x;
	double	y;

	movestep = cube->player->walkdirection * cube->player->movespeed;
	if (cube->player->flag == 1)
	{
		x = cube->p_position_x + cos(cube->player->angle + M_PI / 2) * movestep;
		y = cube->p_position_y + sin(cube->player->angle + M_PI / 2) * movestep;
	}
	else
	{
		x = cube->p_position_x + cos(cube->player->angle) * movestep;
		y = cube->p_position_y + sin(cube->player->angle) * movestep;
	}
	if (!is_a_wall(x / SCALE, cube->p_position_y / SCALE, cube))
		cube->p_position_x = x;
	if (!is_a_wall(cube->p_position_x / SCALE, y / SCALE, cube))
		cube->p_position_y = y;
	cube->player->angle += cube->player->turndirection * \
	cube->player->rotationspeed;
}

int	close_x(void)
{
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	cube->player = malloc(sizeof(t_player));
	cube->img = malloc(sizeof(t_img));
	cube->stable = malloc(sizeof(t_const));
	if (argc != 2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	ft_struct_init(argv, cube);
	cub_draw(cube);
	mlx_hook(cube->mlx_window, 02, (1L << 0), press_key_hook, cube);
	mlx_hook(cube->mlx_window, 03, (1L << 1), release_key_hook, cube);
	mlx_loop_hook(cube->mlx_init, cub_draw, cube);
	mlx_hook(cube->mlx_window, 17, 0, close_x, cube);
	mlx_loop(cube->mlx_init);
	ft_free_parsing(cube);
}
