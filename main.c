/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/23 00:10:48 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "Get_next_line/get_next_line.h"


// void	ft_create_window(t_cube *cube)
// {
	
// }

t_cube	*ft_struct_init(char **argv)
{
	t_cube *cube;
	cube = malloc(sizeof(t_cube));
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->MapWidth * 35, cube->MapHeight * 35, "cube");
	mlx_loop(cube->mlx_init);
	
	return (cube);
}

int main(int argc, char **argv)
{
    t_cube *cube;

	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	cube = ft_struct_init(argv);
	ft_print_cube(cube);
	ft_free_parsing(cube);
    // system("leaks Cub3d");	
}