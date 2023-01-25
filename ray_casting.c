/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:50:07 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/24 23:54:47 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	cast_loop_horiz(t_casting *cast, t_cube *cube)
{
	while (cast->xnext >= 0 && cast->xnext < cube->stable->width && \
	cast->ynext >= 0 && cast->ynext < cube->stable->height)
	{
		if (is_a_wall(cast->xnext / SCALE, cast->ynext / SCALE, cube))
		{
			cube->player->horizx = cast->xnext;
			cube->player->horizy = cast->ynext;
			return (sqrt((cast->xnext - cube->p_position_x) * \
			(cast->xnext - cube->p_position_x) + (cast->ynext - \
			cube->p_position_y) * (cast->ynext - cube->p_position_y)));
		}
			cast->xnext += cast->xstep;
			cast->ynext += cast->ystep;
	}
	return (INT_MAX);
}

double	cast_loop_virtical(t_casting *cast, t_cube *cube)
{
	while (cast->xnext >= 0 && cast->xnext < cube->stable->width && \
	cast->ynext >= 0 && cast->ynext < cube->stable->height)
	{
		if (is_a_wall(cast->xnext / SCALE, cast->ynext / SCALE, cube))
		{
			cube->player->verticalx = cast->xnext;
			cube->player->verticaly = cast->ynext;
			return (sqrt((cast->xnext - cube->p_position_x) * \
			(cast->xnext - cube->p_position_x) + (cast->ynext - \
			cube->p_position_y) * (cast->ynext - cube->p_position_y)));
		}
			cast->xnext += cast->xstep;
			cast->ynext += cast->ystep;
	}
	return (INT_MAX);
}

double	cast_horizntal(t_cube *cube, double angle)
{
	t_casting	cast;

	cast.yintercept = floor(cube->p_position_y / SCALE) * SCALE;
	if (is_down(angle))
		cast.yintercept += SCALE;
	cast.xintercept = cube->p_position_x + \
		(cast.yintercept - cube->p_position_y) / tan(angle);
	cast.ystep = SCALE;
	cast.xstep = SCALE / tan(angle);
	if (!is_down(angle))
		cast.ystep *= -1;
	if (!is_right(angle) && cast.xstep > 0)
		cast.xstep *= -1;
	else if (is_right(angle) && cast.xstep < 0)
		cast.xstep *= -1;
	cast.xnext = cast.xintercept;
	cast.ynext = cast.yintercept;
	if (!is_down(angle))
		cast.ynext -= 1;
	return (cast_loop_horiz(&cast, cube));
}

double	cast_vertical(t_cube *cube, double angle)
{
	t_casting	cast;

	cast.xintercept = floor(cube->p_position_x / SCALE) * SCALE;
	if (is_right(angle))
		cast.xintercept += SCALE;
	cast.yintercept = cube->p_position_y + (cast.xintercept - \
		cube->p_position_x) * tan(angle);
	cast.xstep = SCALE;
	cast.ystep = SCALE * tan(angle);
	if (!is_right(angle))
		cast.xstep *= -1;
	if (!is_down(angle) && cast.ystep > 0)
		cast.ystep *= -1;
	else if (is_down(angle) && cast.ystep < 0)
		cast.ystep *= -1;
	cast.xnext = cast.xintercept;
	cast.ynext = cast.yintercept;
	if (!is_right(angle))
		cast.xnext -= 1;
	return (cast_loop_virtical(&cast, cube));
}
