/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:51:48 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/22 20:01:40 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return ;
	dst = cube->img->addr + (y * cube->img->size_len + x * \
	(cube->img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	rectengale(int x, int y, int x1, int y1, t_cube *cube, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < y1)
	{
		j = 0;
		while (j < x1)
		{
			my_mlx_pixel_put(cube, j + x, i + y, color);
			j++;
		}
		i++;
	}
}

void	ft_new_image(t_cube *cube)
{
	cube->img->img = mlx_new_image(cube->mlx_init, WINDOW_WIDTH, \
	WINDOW_HEIGHT);
	cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, \
	&cube->img->size_len, &cube->img->endian);
}
