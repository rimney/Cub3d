/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:58:41 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/13 03:49:07 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void rander_player(t_cube *cube)
{
	draw_circle(cube->P_position_x * SCALE, cube->P_posotion_y * SCALE, cube->img,  0x00FF0000);
}

void cub_draw(t_cube *cube)
{
	render_map(cube);
	rander_player(cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img, 0, 0);

}