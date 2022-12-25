/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/25 21:14:54 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "Get_next_line/get_next_line.h"

void	render_background(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (i < cube->MapHeight * SCALE)
	{
		j = 0;
		while(j < cube->MapWidth * SCALE)
		{
			mlx_pixel_put(cube->mlx_init, cube->mlx_window, j, i, 0xFCD088);
			j++;
		}
		i++;
	}
}

// void	my_pixel_put(t_cube *cube, int x, int y, int color)
// {
// 	char *pixel;
// 	int i;

// 	i = 0;
// 	pixel = cube->img->addr + (y * cube->img->size_len + x * (cube->img->bpp / 8));
// 	while (i >= 0)
// 	{
// 		if(cube->img->endian)
// 			*pixel++ = (color >> i) & 0xFF;
// 		else
// 			*pixel++ = (color >> (cube->img->bpp - 8 - i)) & 0xFF;
// 		i -= 8;
// 	}
// }

void	my_pixel_put(t_cube *cube, int x, int y, int color)
{
	char    *pixel;

    pixel = cube->img->addr + (y * cube->img->size_len + x * (cube->img->bpp / 8));
	*(int *)pixel = color;
	printf("%d <\n", x);
	printf("%d <\n", y);
}

int render_block(t_cube *cube, int x, int y, int w, int h)
{
	int i;
	int j;

	i = y;
	while(i < y + h)
	{
		j = x;
		while (j < w + x)
		{
			my_pixel_put(cube, j, i, 0xFF0000);
			j++;
		}
		i++;
	}
	return (0);
}

int	render(t_cube *cube, t_img *img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	img->addr = mlx_get_data_addr(cube->img->img, &img->bpp, &img->size_len, &img->endian);
	// while(j < cube->MapWidth)
	// {
		render_block(cube, (cube->MapWidth * SCALE), (cube->MapHeight * SCALE), SCALE, SCALE);
		render_block(cube, 0, 0, SCALE, SCALE);
	// }
	return (0);
}


void	ft_create_window(t_cube *cube, t_img *img)
{
	int i = 0;
	int j = 0;

	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE, "cube");
	img->img = mlx_new_image(cube->mlx_init, cube->MapWidth * 50, cube->MapHeight * 50);
	render(cube, img);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, img->img ,i, j);
	mlx_loop(cube->mlx_init);
}

void	ft_img_init(t_img *img)
{
	img->bpp = 0;
	img->endian = 0;
	img->size_len = 0;
	img->addr = NULL;
}

t_cube	*ft_struct_init(char **argv, t_img *img)
{
	t_cube *cube;
	cube = malloc(sizeof(t_cube));
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	ft_img_init(img);
	cube->img = img;
	ft_create_window(cube, img);

	return (cube);
}

int main(int argc, char **argv)
{
    t_cube	*cube;
	t_img	img;
	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	cube = ft_struct_init(argv, &img);
	ft_print_cube(cube);
	ft_free_parsing(cube);
    // system("leaks Cub3d");
}