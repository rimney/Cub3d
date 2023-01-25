/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:51:48 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/25 04:45:28 by rimney           ###   ########.fr       */
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

void	ft_new_image(t_cube *cube)
{
	cube->img->img = mlx_new_image(cube->mlx_init, WINDOW_WIDTH, \
	WINDOW_HEIGHT);
	cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, \
	&cube->img->size_len, &cube->img->endian);
}

void	floor_ceeling_render(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(cube, j, i, cube->c);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(cube, j, i + WINDOW_HEIGHT / 2, cube->f);
			j++;
		}
		i++;
	}
}

int	ft_check_extension(char **argv)
{
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".cub", 4) == 0)
		return (1);
	return (0);
}
