/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:51:48 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/18 19:15:26 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;
	
	if (x < 0 || x > cube->stable->width || y < 0 || y > cube->stable->height)
		return ;
	dst = cube->img->addr + (y * cube->img->size_len + x * (cube->img->bpp / 8));
	*(unsigned int*)dst = color;
}


void ft_draw_line(int X0, int Y0, int X1, int Y1, t_cube *cube, unsigned int color)
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
        my_mlx_pixel_put(cube, round(X), round(Y),
                 color); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
// for visualization of line-
                    // generation step by step
	
		}
}
void	draw_circle(int x, int y, t_cube *cube, unsigned int color)
{
	double	i;
	double	x1;
	double	y1, angle;
	int		k;

	k = 0;
	while (k < 8)
	{
		i = 0;
		while (i < 360)
		{
				angle = i;
				x1 = k * cos(angle * M_PI / 180);
				y1 = k * sin(angle * M_PI / 180);
				my_mlx_pixel_put(cube, x + x1, y + y1, color);
				i += 0.1;	
		}
		k++;
	}
}

void rectengale(int x, int y, t_cube *cube, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SCALE)
	{
		j = 0;
		while (j < SCALE)
		{
			my_mlx_pixel_put(cube, j + x, i + y, color);
			j++;
		}
		i++;
	}
}
