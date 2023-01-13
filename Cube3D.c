/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cube3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:03:45 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/13 04:09:38 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void cub_update()
{

}

int press_key_hook(int key, t_cube *cube)
{
	if (key == 13)
		cube->player->walkdirection += 1;
	else if (key == 1)
		cube->player->walkdirection -= 1;
	else if (key == 123)
		cube->player->turndirection -= -1;
	else if (key == 124)
		cube->player->turndirection += 1;
	return (0);
}

int release_key_hook(int key, t_cube *cube)
{
	if (key == 13)
		cube->player->walkdirection = 0;
	else if (key == 1)
		cube->player->walkdirection = 0;
	else if (key == 123)
		cube->player->turndirection = 0;
	else if (key == 124)
		cube->player->turndirection = 0;
	return (0);
}

int main(int argc, char **argv)
{
    t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	cube->player = malloc(sizeof(t_player));
	cube->img = malloc(sizeof(t_img));

	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	ft_struct_init(argv, cube);
	ft_print_cube(cube);
	cub_draw(cube);
	mlx_hook(cube->mlx_window, 02, (1L<<0), press_key_hook, cube);
	mlx_hook(cube->mlx_window, 03, (1L<<1), release_key_hook, cube);
	mlx_loop(cube->mlx_init); 
	ft_free_parsing(cube);
}