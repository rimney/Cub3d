/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/28 03:31:46 by rimney           ###   ########.fr       */
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

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->size_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int render_block(t_cube *cube, int x, int y, int w, int h, int color)
{
	int i;
	int j;

	i = y;
	while(i < y + h)
	{
		j = x;
		while (j < w + x)
		{
			my_pixel_put(cube->img, j, i, color);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_render_lines_vertical(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = SCALE;
	while(j < cube->MapWidth * SCALE)
	{
		i = 0;
		while(i < cube->MapHeight * SCALE)
		{
			my_pixel_put(cube->img, j, i, 0xFF0000);
			i++;
		}
		j += SCALE;
	}
}

void	ft_render_lines_horizental(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = SCALE;
	while(j < cube->MapHeight * SCALE)
	{
		i = 0;
		while(i < cube->MapWidth * SCALE)
		{
			my_pixel_put(cube->img, i, j, 0xFF0000);
			i++;
		}
		j += SCALE;
	}
}

void	ft_render_lines(t_cube *cube)
{
	ft_render_lines_vertical(cube);
	ft_render_lines_horizental(cube);
}

void	ft_render_player(t_cube *cube)
{
	// int i = 0;
	// int j = 0;

	// i = cube->P_position_x;
	// j = cube->P_posotion_y;
	// mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, img->img ,i, j);
		printf("%f << Y\n", cube->P_posotion_y);
	render_block(cube, cube->P_position_x * SCALE, cube->P_posotion_y * SCALE, SCALE, SCALE, 0xFF0000);


}

void	ft_move_player_forward(t_cube *cube)
{
	cube->P_posotion_y -= 1;
	printf("%f <<\n", cube->P_posotion_y);
}

int	key_hook(int key, t_cube *cube)
{
	printf("%d <<\n", key);
	if(key == 0)
		printf("A\n");
	if(key == 1)
		printf("S\n");
	if(key == 2)
		printf("D\n");
	if (key == 13)
	{
		ft_move_player_forward(cube);
		printf("W\n");
	}
	if (key == 123)
		printf("LEFT\n");
	if (key == 124)
		printf("right\n");
	if (key == 125)
		printf("DOWN\n");
	if (key == 126)
		printf("UP\n");
	if(cube)
		return (0);
	return (0);
}

int	render(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < cube->MapHeight)
	{
		j = 0;
		while((size_t)j < ft_strlen(cube->Map[i]))
		{
			if(cube->Map[i][j] == '1')
				render_block(cube, j * SCALE, i * SCALE, SCALE, SCALE, 0xFFFFFF);
			if(cube->Map[i][j] == '0')
				render_block(cube, j * SCALE, i * SCALE, SCALE, SCALE, 0x0000FF);
			if(is_a_direction(cube->Map[i][j]))
				render_block(cube, j * SCALE, i * SCALE, SCALE, SCALE, 0x0000FF);
			j++;
		}
		i++;
	}
	ft_render_lines(cube);
	ft_render_player(cube);

	if(cube->render)
		mlx_clear_window(cube->mlx_init, cube->mlx_window);
	cube->render = 1;
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img ,i, j);
	return (0);
}


void	ft_create_window(t_cube *cube, t_img *img)
{
	int i = 0;
	int j = 0;

	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE, "cube");
	img->img = mlx_new_image(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE);
	img->addr = mlx_get_data_addr(cube->img->img, &img->bpp, &img->size_len, &img->endian);
	render(cube);
	// ft_render_player(cube);
	cube->img = img;
	mlx_key_hook(cube->mlx_window, key_hook, cube);
	mlx_loop_hook(cube->mlx_init, render, cube);
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