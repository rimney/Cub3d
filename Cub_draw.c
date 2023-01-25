/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 02:58:41 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/25 02:21:47 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_color_from_img(t_img *img, int x, int y)
{
	char	*ret;

	ret = img->addr + (y * img->size_len + x
			* (img->bpp / 8));
	return (*(int *)ret);
}

void	render_loop(t_cube *cube, t_render *render, int i)
{
	int	j;

	j = render->wallt;
	while (j < render->wallb)
	{
		render->distance_top = j + (render->wallstripeheight / 2) - \
		(WINDOW_HEIGHT / 2);
		cube->texture_offs_y = render->distance_top * \
		((float)cube->texture->height / render->wallstripeheight);
		cube->texture_color = get_color_from_img(cube->texture, \
		cube->texture_offs_x, cube->texture_offs_y);
		my_mlx_pixel_put(cube, i, j, cube->texture_color);
		j++;
	}
}

void	render3d(t_cube *cube, t_ray *ray, int i)
{
	t_render	render;

	render.pdistance = ray[i].raydistance * cos(ray[i].ray_angle - \
	cube->player->angle);
	render.dpp = (WINDOW_WIDTH / 2) / tan(cube->stable->fov / 2);
	render.projectionwallheight = (SCALE / render.pdistance) * render.dpp;
	render.wallstripeheight = (int)render.projectionwallheight;
	render.wallt = (WINDOW_HEIGHT / 2) - (render.wallstripeheight / 2);
	if (render.wallt < 0)
		render.wallt = 0;
	render.wallb = (WINDOW_HEIGHT / 2) + (render.wallstripeheight / 2);
	if (render.wallb > WINDOW_HEIGHT)
		render.wallb = WINDOW_HEIGHT;
	if (ray[i].is_vertical_hit)
		cube->texture_offs_x = (int)ray[i].wall_hit_point_y % SCALE;
	else
		cube->texture_offs_x = (int)ray[i].wall_hit_point_x % SCALE;
	render_loop(cube, &render, i);
}

void	distance_check(t_ray *rays, t_cube *cube, t_casting *cast, int i)
{
	if (cast->horizdestance < cast->verdistance)
	{
		rays[i].wall_hit_point_x = cube->player->horizx;
		rays[i].wall_hit_point_y = cube->player->horizy;
		rays[i].raydistance = cast->horizdestance;
		rays[i].ray_angle = cast->angle;
		rays[i].is_vertical_hit = 0;
		if (rays[i].ray_angle >= 0 && rays[i].ray_angle <= M_PI)
			cube->texture = cube->so_texture;
		else
			cube->texture = cube->no_texture;
	}
	else
	{
		rays[i].wall_hit_point_x = cube->player->verticalx;
		rays[i].wall_hit_point_y = cube->player->verticaly;
		rays[i].raydistance = cast->verdistance;
		rays[i].is_vertical_hit = 1;
		rays[i].ray_angle = cast->angle;
		if (rays[i].ray_angle >= M_PI / 2 && rays[i].ray_angle <= 3 * M_PI / 2)
			cube->texture = cube->we_texture;
		else
			cube->texture = cube->ea_texture;
	}
}

void	cast_all_ray(t_cube *cube)
{
	t_ray		*rays;
	t_casting	cast;
	int			i;

	i = 0;
	rays = malloc(sizeof(t_ray) * cube->stable->num_of_rays + 1);
	cast.angle = cube->player->angle - (cube->stable->fov / 2);
	while (i < cube->stable->num_of_rays)
	{
		resize_angle(&cast.angle);
		cast.horizdestance = cast_horizntal(cube, cast.angle);
		cast.verdistance = cast_vertical(cube, cast.angle);
		distance_check(rays, cube, &cast, i);
		render3d(cube, rays, i);
		i++;
		cast.angle += cube->stable->fov / cube->stable->num_of_rays;
	}
	free(rays);
}
