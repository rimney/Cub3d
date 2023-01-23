/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:03:45 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/24 00:31:48 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_a_wall(int x, int y, t_cube *cube)
{
	if (x < 0 || x > cube->stable->width || y < 0 || y > cube->stable->height)
		return (1);
	if ((size_t)x < ft_strlen(cube->Map[y]) && cube->Map[y][x] == '1')
		return (1);
	return (0);
}

void	update_player(t_cube *cube)
{
	double	movestep;
	double	x;
	double	y;

	movestep = cube->player->walkdirection * cube->player->movespeed;
	x = cube->P_position_x + cos(cube->player->angle) * movestep;
	y = cube->P_position_y + sin(cube->player->angle) * movestep;
	if (!is_a_wall(x / SCALE, cube->P_position_y / SCALE, cube))
		cube->P_position_x = x;
	if (!is_a_wall(cube->P_position_x / SCALE, y / SCALE, cube))
		cube->P_position_y = y;
	cube->player->angle += cube->player->turndirection * \
	cube->player->rotationspeed;
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
	ft_print_cube(cube);
	cub_draw(cube);
	mlx_hook(cube->mlx_window, 02, (1L << 0), press_key_hook, cube);
	mlx_hook(cube->mlx_window, 03, (1L << 1), release_key_hook, cube);
	mlx_loop_hook(cube->mlx_init, cub_draw, cube);
	mlx_loop(cube->mlx_init);
	ft_free_parsing(cube);
}
