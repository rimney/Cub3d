/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:58:41 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/19 23:36:02 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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
				rectengale(x * SCALE, y * SCALE, cube, 0x0040403D);
			if (cube->Map[y][x] == '0' || cube->Map[y][x] == 'E' )
				rectengale(x * SCALE, y * SCALE, cube, 0x00FFFFFF);
			x++;
		}
		y++;
	}
}

void rander_player(t_cube *cube)
{
	double x1;
	double y1;

	x1 = cos(cube->player->angle) * 100;
	y1 = sin(cube->player->angle) * 100;
	draw_circle(cube->P_position_x, cube->P_position_y, cube,  0x0FF00000);
}



double cast_horizntal(t_cube *cube, double angle)
{

	double xstep, ystep, xintercept, yintercept;
	double	xnext, ynext;

	yintercept = floor(cube->P_position_y / SCALE) * SCALE;
	if(is_down(angle))
		yintercept += SCALE;
	xintercept = cube->P_position_x + (yintercept - cube->P_position_y) / tan(angle);
	ystep = SCALE;
	xstep =  SCALE / tan(angle);
	if (!is_down(angle))
		ystep *= -1;
	if (!is_right(angle) && xstep > 0)
		xstep *= -1;
	else  if (is_right(angle) && xstep < 0)
		xstep *= -1;
		
	xnext = xintercept;
	ynext = yintercept;
		if(!is_down(angle))
			ynext -= 1;
	while (xnext >= 0 && xnext < cube->stable->width && ynext >= 0 && ynext < cube->stable->height)
	{
		if (is_a_wall(xnext / SCALE, ynext / SCALE, cube))
		{
			cube->player->horizx = xnext;
			cube->player->horizy = ynext;
			return (sqrt((xnext - cube->P_position_x) * (xnext - cube->P_position_x) + (ynext - cube->P_position_y) * (ynext - cube->P_position_y)));
		}
			xnext += xstep;
			ynext += ystep;
	}
	return (INT_MAX);
}

double cast_vertical(t_cube *cube, double angle)
{

	double xstep, ystep, xintercept, yintercept;
	double	xnext, ynext;
	
	xintercept = floor(cube->P_position_x / SCALE) * SCALE;
	if(is_right(angle))
		xintercept += SCALE;
	yintercept = cube->P_position_y + (xintercept - cube->P_position_x) * tan(angle);
	xstep = SCALE;
	ystep =  SCALE * tan(angle);
	if (!is_right(angle))
		xstep *= -1;
	if (!is_down(angle) && ystep > 0)
		ystep *= -1;
	else  if (is_down(angle) && ystep < 0)
		ystep *= -1;
		
	xnext = xintercept;
	ynext = yintercept;
	if(!is_right(angle))
			xnext -= 1;
	while (xnext >= 0 && xnext < cube->stable->width && ynext >= 0 && ynext < cube->stable->height)
	{
		if (is_a_wall(xnext / SCALE, ynext / SCALE, cube))
		{
			cube->player->verticalx = xnext;
			cube->player->verticaly = ynext;
			return (sqrt((xnext - cube->P_position_x) * (xnext - cube->P_position_x) + (ynext - cube->P_position_y) * (ynext - cube->P_position_y)));
		}
			xnext += xstep;
			ynext += ystep;
	}
	return (INT_MAX);
}

void cast_all_ray(t_cube *cube)
{
	double	angle, verdistance, horizdestance;
	int		i;

	i = 0;
	angle = cube->player->angle - (cube->stable->fov / 2);
	while (i < cube->stable->num_of_rays)
	{
		resize_angle(&angle);
		horizdestance =  cast_horizntal(cube, angle);
		verdistance =  cast_vertical(cube, angle);
		if (horizdestance < verdistance)
			ft_draw_line(cube->P_position_x, cube->P_position_y, cube->player->horizx, cube->player->horizy, cube, 0x00FF0000);
		else
			ft_draw_line(cube->P_position_x, cube->P_position_y, cube->player->verticalx, cube->player->verticaly, cube, 0x00FF0000);
			
		i++;
		angle += cube->stable->fov / cube->stable->num_of_rays;
	}
}

int cub_draw(t_cube *cube)
{
	ft_new_image(cube);
	update_player(cube);
	render_map(cube);
	cast_all_ray(cube);
	rander_player(cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img, 0, 0);
	mlx_destroy_image(cube->mlx_init, cube->img->img);
	return (0);
}
