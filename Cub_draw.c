/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:58:41 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/14 17:56:16 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void test(t_cube *cube);
void	draw_circle(int x, int y, t_img *img, unsigned int color)
{
	double	i;
	double	x1;
	double	y1, angle;
	int		k;

	k = 1;
	while (k < 8)
	{
		i = 0;
		while (i < 360)
		{
				angle = i;
				x1 = k * cos(angle * M_PI / 180);
				y1 = k * sin(angle * M_PI / 180);
				my_mlx_pixel_put(img, x + x1, y + y1, color);
				i += 0.1;	
		}
		k++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	dst = img->addr + (y * img->size_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void rectengale(int x, int y, t_img *img, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			my_mlx_pixel_put(img, j + x, i + y, color);
			j++;
		}
		i++;
	}
}

void render_map(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (cube->Map[y])
	{
		x = 0;
		while (cube->Map[y][x])
		{
			if (cube->Map[y][x] == '1')
				rectengale(x * SCALE, y * SCALE, cube->img, 0x0040403D);
			if (cube->Map[y][x] == '0')
			rectengale(x * SCALE, y * SCALE, cube->img, 0x00FFFFFF);
			x++;
		}
		y++;
	}
}
void DDA(int X0, int Y0, int X1, int Y1, t_img *img)
{
	// calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = X0;
    float Y = Y0;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(img, round(X), round(Y),
                 0x0FF0000); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
// for visualization of line-
                    // generation step by step
	
}
}

void rander_player(t_cube *cube)
{
	double x1;
	double y1;

	x1 = cos(cube->player->angle);
	y1 = sin(cube->player->angle);
	draw_circle(cube->P_position_x * SCALE, cube->P_posotion_y * SCALE, cube->img,  0x00FF0000);
	DDA(cube->P_position_x * SCALE, cube->P_posotion_y * SCALE, (cube->P_position_x + x1) * SCALE, (cube->P_posotion_y + y1) * SCALE, cube->img);
}

int cub_draw(t_cube *cube)
{
	test(cube);
	update_player(cube);
	render_map(cube);
	rander_player(cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img, 0, 0);
	mlx_destroy_image(cube->mlx_init, cube->img->img);
	return (0);
}