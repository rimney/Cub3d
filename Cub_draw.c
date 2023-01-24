/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:58:41 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/24 17:11:17 by rimney           ###   ########.fr       */
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
	while (cube->map[y])
	{
		x = 0;
		while (cube->map[y][x])
		{
			if (cube->map[y][x] == '1')
				rectengale(x * SCALE, y * SCALE, SCALE, SCALE, cube, 0x0040403D);
			if (cube->map[y][x] == '0' || cube->map[y][x] == 'E' )
				rectengale(x * SCALE, y * SCALE, SCALE, SCALE, cube, 0x00FFFFFF);
			x++;
		}
		y++;
	}
}


double cast_horizntal(t_cube *cube, double angle)
{

	double xstep, ystep, xintercept, yintercept;
	double	xnext, ynext;

	yintercept = floor(cube->p_position_y / SCALE) * SCALE;
	if(is_down(angle))
		yintercept += SCALE;
	xintercept = cube->p_position_x + (yintercept - cube->p_position_y) / tan(angle);
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
			return (sqrt((xnext - cube->p_position_x) * (xnext - cube->p_position_x) + (ynext - cube->p_position_y) * (ynext - cube->p_position_y)));
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
	
	xintercept = floor(cube->p_position_x / SCALE) * SCALE;
	if(is_right(angle))
		xintercept += SCALE;
	yintercept = cube->p_position_y + (xintercept - cube->p_position_x) * tan(angle);
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
			return (sqrt((xnext - cube->p_position_x) * (xnext - cube->p_position_x) + (ynext - cube->p_position_y) * (ynext - cube->p_position_y)));
		}
			xnext += xstep;
			ynext += ystep;
	}
	return (INT_MAX);
}

int	get_color_from_img(t_img *img, int x, int y)
{
	char	*ret;

	ret = img->addr + (y * img->size_len + x
			* (img->bpp / 8));
	return (*(int *)ret);
}

void	render3D(t_cube *cube, t_ray *ray, int i)
{
	int j;
	double pdistance;
	double dpp;
	double projectionwallheight;
	int wallstripeheight;
	int walltoppixel;
	int wallbottompixel;
	int distance_top;
	
	
	pdistance = ray[i].raydistance * cos(ray[i].ray_angle - cube->player->angle);
	dpp = (WINDOW_WIDTH / 2) / tan(cube->stable->fov / 2);
	projectionwallheight = (SCALE / pdistance) * dpp;
	wallstripeheight = (int)projectionwallheight;
	walltoppixel = (WINDOW_HEIGHT / 2) - (wallstripeheight / 2);
	walltoppixel =  walltoppixel < 0 ? 0 : walltoppixel;
	wallbottompixel = (WINDOW_HEIGHT / 2) + (wallstripeheight / 2);
	wallbottompixel = wallbottompixel > WINDOW_HEIGHT ? WINDOW_HEIGHT: wallbottompixel;
	j = walltoppixel;
	if(ray[i].is_vertical_hit)
		cube->texture_offs_x = (int)ray[i].wall_hit_point_y % SCALE;
	else
		cube->texture_offs_x = (int)ray[i].wall_hit_point_x % SCALE;
	while(j < wallbottompixel)
	{
		distance_top = j + (wallstripeheight / 2) - (WINDOW_HEIGHT / 2);
		cube->texture_offs_y = distance_top * ((float)cube->texture->height / wallstripeheight);
		cube->texture_color = get_color_from_img(cube->texture, cube->texture_offs_x, cube->texture_offs_y);
		my_mlx_pixel_put(cube, i, j, cube->texture_color);
		j++;
	}
}

t_ray *cast_all_ray(t_cube *cube)
{
	t_ray *rays;
	double	angle, verdistance, horizdestance;
	int		i;

	i = 0;
	rays = malloc(sizeof(t_ray) * cube->stable->num_of_rays + 1);
	angle = cube->player->angle - (cube->stable->fov / 2);
	while (i < cube->stable->num_of_rays )
	{
		resize_angle(&angle);
		horizdestance =  cast_horizntal(cube, angle);
		verdistance =  cast_vertical(cube, angle);
		if (horizdestance < verdistance)
		{
			rays[i].wall_hit_point_x = cube->player->horizx;
			rays[i].wall_hit_point_y =  cube->player->horizy;
			rays[i].raydistance = horizdestance;
			rays[i].ray_angle = angle;
			rays[i].is_vertical_hit = 0;
			if(rays[i].ray_angle >= 0 &&  rays[i].ray_angle <= M_PI)
				cube->texture = cube->so_texture;
			else
				cube->texture = cube->no_texture;
		}
		else
		{
			rays[i].wall_hit_point_x =  cube->player->verticalx;
			rays[i].wall_hit_point_y = cube->player->verticaly;
			rays[i].raydistance = verdistance;
			rays[i].is_vertical_hit = 1;
			rays[i].ray_angle = angle;
			if(rays[i].ray_angle >= M_PI / 2 && rays[i].ray_angle <= 3 * M_PI / 2)
				cube->texture = cube->we_texture;
			else
				cube->texture = cube->ea_texture;
		}
		render3D(cube, rays, i);
		i++;
		angle += cube->stable->fov / cube->stable->num_of_rays;
	}
	return (rays);
}

void floor_ceeling_render(t_cube *cube)
{
	rectengale(0, 0,WINDOW_WIDTH, WINDOW_HEIGHT / 2, cube, cube->c);
	rectengale(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2, cube, cube->f);
}

int cub_draw(t_cube *cube)
{
	ft_new_image(cube);
	update_player(cube);
	floor_ceeling_render(cube);
	cast_all_ray(cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img, 0, 0);
	mlx_destroy_image(cube->mlx_init, cube->img->img);
	return (0);
}
