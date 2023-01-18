/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:58:41 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/18 13:19:47 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void ft_new_image(t_cube *cube);
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

	i = 4;
	while (i < SCALE)
	{
		j = 4;
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
                 0xFF00000); // put pixel at (X,Y)
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
	draw_circle(cube->P_position_x * SCALE, cube->P_posotion_y * SCALE, cube->img,  0x00000000);
	DDA(cube->P_position_x * SCALE, cube->P_posotion_y * SCALE, (cube->P_position_x + x1) * SCALE, (cube->P_posotion_y + y1) * SCALE, cube->img);
}
void	castallray(t_cube *cube);
int cub_draw(t_cube *cube)
{
	ft_new_image(cube);
	update_player(cube);
	render_map(cube);
	rander_player(cube);
	castallray(cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img, 0, 0);
	mlx_destroy_image(cube->mlx_init, cube->img->img);
	return (0);
}

int is_down(double angle)
{
	if (angle > 0 && angle < M_PI)
		return (1);
	return (0);
}

int	is_right(double angle)
{
	if (angle > 1.5 * M_PI || angle < 0.5 * M_PI)
		return (1);
	return (0);
}

void resize_angle(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += 2 * M_PI;
}

void	ray(t_cube  *cube, double angle)
{
	double	x;
	double	y;
	double xstep= 0, ystep = 0, xinter= 0 , yinter =0;
	double nextx, nexty;
	x = cos(angle) * 2;
	y = sin(angle) * 2;
	
	yinter = floor(cube->P_posotion_y) * SCALE;
	xinter = cube->P_position_x * SCALE + (yinter - cube->P_posotion_y * SCALE) / tan(angle);

	if (is_down(angle))
		yinter += SCALE;
	ystep = SCALE;
	if (!is_down(angle))
		ystep *= -1;
	xstep = SCALE / tan(angle);
	if (!is_right(angle) && xstep > 0)	
		xstep *= -1;
	if (is_right(angle) && xstep < 0)
		xstep *= -1;
	nextx = xinter;
	nexty = yinter;
	// if (!is_down(angle))
	// {
	// 	printf("here\n");	
	// 	yinter -= 32;
	// }
	while(nextx >= 0 && nextx < cube->MapWidth * SCALE && nexty >= 0 && nexty < cube->MapHeight * SCALE)
	{
		while (lroundf(nextx) % 32 != 0)
			nextx--;
		while (lroundf(nexty) % 32 != 0)
			nexty--;
			nexty--;
		while (lroundf(nexty) % 32 != 0)
			nexty--;
		if (!hasawall(round(nextx / SCALE), round(nexty / SCALE), cube))
		{
			printf("%f, %f\n", nextx / SCALE, nexty / SCALE);
			DDA(cube->P_position_x * SCALE, cube->P_posotion_y * SCALE,
			nextx, nexty, cube->img);
			break;
		}
		nextx += xstep;
		nexty += ystep;
	}
}


void	castallray(t_cube *cube)
{
	int		i;
	double	angle;
	 
	i = 0;
	angle = cube->player->angle - (cube->player->fov / 2);
	resize_angle(&angle);
	// while (i < cube->player->num_of_rays)
	while (i < 1)
	{
		ray(cube, angle);
		angle += cube->player->fov / cube->player->num_of_rays;
		i++;
	}
}
