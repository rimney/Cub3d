/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2022/12/29 04:36:43 by rimney           ###   ########.fr       */
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


void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->size_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
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

int ft_abs(int n) { return ((n > 0) ? n : (n * (-1))); }

void	DDA(t_cube *cube, int x1, int y1)
{
	int dx;
	int dy;
	int steps;
	float Xinc;	
	float Yinc;
	double X;
	double Y;
	int i;

	i = 1;
	dx = x1 - cube->player->x;
	dy = y1 - cube->player->y;
	steps = ft_abs(dx) > ft_abs(dy) ? ft_abs(dx) : ft_abs(dy);
	Xinc = dx / (float)steps;
	Yinc = dy / (float)steps;
	X = cube->player->x;
	Y = cube->player->y;
	while(i <= 60)
	{
		my_pixel_put(cube->img, round(X), round(Y), 0xFF0000);
		i++;
		X += Xinc;
		Y += Yinc; 
	}
}

void ft_drawline(t_cube *cube, int x1, int y1)
{
    int dx, dy, p, x, y;
 
dx=x1-cube->player->x;
dy=y1-cube->player->y;
 
x=cube->player->x;
y=cube->player->y;
 
p=2*dy-dx;
 
while(x<x1)
{
if(p>=0)
{
	my_pixel_put(cube->img, x,y, 0xFF0000);
y=y+1;
p=p+2*dy-2*dx;
}
else
{
	my_pixel_put(cube->img, x,y, 0xFF0000);
p=p+2*dy;
}
x=x+1;
}
}

void	ft_render_player(t_cube *cube)
{
	// int player_X;
	// int player_Y;
	double movestep;
	// player_X = 
	movestep = cube->player->walkdirection * cube->player->movespeed;
	
	cube->player->rotationangle += (cube->player->turndirection * cube->player->rotationspeed);
	cube->player->x += cos(cube->player->rotationangle) * movestep;
	cube->player->y += sin(cube->player->rotationangle) * movestep;
	DDA(cube, cos(cube->player->rotationangle) * 90 * SCALE, sin(cube->player->rotationangle) * 90 * SCALE);
	render_block(cube, cube->player->x, cube->player->y, SCALE / 4, SCALE / 4 , 0xFF0000);
}

int	key_press(int key, t_cube *cube)
{
	if(key == UP_KEY || key == W_KEY)
		cube->player->walkdirection = 1;
	else if (key == DOWN_KEY || key == S_KEY)
		cube->player->walkdirection = -1;
	else if (key == RIGHT_KEY)
		cube->player->turndirection = 1;
	else if (key == LEFT_KEY)
		cube->player->turndirection = -1;

	return (0);
}

int	key_release(int key, t_cube *cube)
{
	if(key == UP_KEY || key == W_KEY)
		cube->player->walkdirection = 0;
	else if (key == DOWN_KEY || key == S_KEY)
		cube->player->walkdirection = 0;
	else if (key == RIGHT_KEY)
		cube->player->turndirection = 0;
	else if (key == LEFT_KEY)
		cube->player->turndirection = 0;
	return (0);
}


int	render(t_cube *cube)
{
	int i;
	int j;
	int ii;
	int jj;

	i = 0;
	j = 0;
	ii = 0;
	jj = 0;
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
	 mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img ,ii, jj);

	return (0);
}

void	ft_create_window(t_cube *cube, t_img *img)
{
	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE, "cube");
	img->img = mlx_new_image(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE);
	img->addr = mlx_get_data_addr(cube->img->img, &img->bpp, &img->size_len, &img->endian);
	// ft_render_player(cube);
	cube->img = img;
	mlx_hook(cube->mlx_window, 2, 0, key_press, cube);
	mlx_hook(cube->mlx_window, 3, 0, key_release, cube);
	mlx_loop_hook(cube->mlx_init, render, cube);
	mlx_loop(cube->mlx_init);
}

void	ft_init_player(t_cube *cube, t_player *player)
{
	player->x = cube->P_position_x * SCALE;
	player->y = cube->P_posotion_y * SCALE;
	player->radius = 3;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotationangle = PI / 2;
	player->movespeed = 2.0;
	player->rotationspeed = 2 * (PI / 180);
	cube->player = player;
}

void	ft_img_init(t_img *img)
{
	img->bpp = 0;
	img->endian = 0;
	img->size_len = 0;
	img->addr = NULL;
}

t_cube	*ft_struct_init(char **argv, t_img *img, t_player *player)
{
	t_cube *cube;
	cube = malloc(sizeof(t_cube));
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	ft_init_player(cube, player);
	ft_img_init(img);
	cube->img = img;
	ft_create_window(cube, img);

	return (cube);
}

int main(int argc, char **argv)
{
    t_cube	*cube;
	t_img	img;
	t_player player;
	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	cube = ft_struct_init(argv, &img, &player);
	ft_print_cube(cube);
	ft_free_parsing(cube);
    // system("leaks Cub3d");
}