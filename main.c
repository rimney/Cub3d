/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrobaii <mrobaii@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2023/01/13 03:37:04 by mrobaii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "Get_next_line/get_next_line.h"
#include <math.h>



void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void DrawCircle(int x, int y, int color, t_img *img);
void 	draw_line(int x, int y, int color, t_img *img);
void ft_draw(t_cube *cube);
int keyhook(int key, t_cube *cube)
{
	if (key == 126)
	{
		cube->P_position_x += cos(cube->player->angle);
		cube->P_posotion_y += sin(cube->player->angle);
		ft_draw(cube);
	}
	return (0);
}

void	rander_player(int x, int y, int color, t_cube *cube)
{
	x= 0;
	y = 0;
	DrawCircle(cube->P_position_x * SCALE + 18, cube->P_posotion_y * SCALE + 18, color, cube->img);
}

void DrawCircle(int x, int y, int color, t_img *img)
{
      static const double PI = 3.1415926535;
      double i, angle, x1, y1;
	  int k;
	  
	  k = 0;
	  while (k < 5)
	  {
		for(i = 0; i < 360; i += 0.1)
		{
				angle = i;
				x1 = k * cos(angle * PI / 180);
				y1 = k * sin(angle * PI / 180);
				my_mlx_pixel_put(img, x + x1, y + y1, color);
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

void render_rect(int x, int y, t_img *img, unsigned int color)
{
	int i;
	int j;

	i = 4;
	while(i < SCALE)
	{
		j = 4;
		while (j < SCALE)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void render_cube(t_cube *cube)
{
	int i;
	int j;
	
	i = 0;
	while (cube->Map[i])
	{
		j = 0;
		while (cube->Map[i][j])
		{
			if(cube->Map[i][j] == '1')
				render_rect(j * SCALE, i * SCALE, cube->img, 0x00b8df10);
			if(cube->Map[i][j] == '0' || cube->Map[i][j] == 'S')
				render_rect(j * SCALE, i * SCALE, cube->img, 0x00390879);
			j++;
		}
		i++;
	}
}

void ft_draw(t_cube *cube)
{
	render_cube(cube);
	rander_player(cube->P_position_x, cube->P_posotion_y, 0x00FF0000, cube);
	mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img, 0, 0);
	mlx_key_hook(cube->mlx_window, keyhook, cube);
	mlx_loop(cube->mlx_init);
}




int main(int argc, char **argv)
{
    t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	cube->player = malloc(sizeof(t_player));
	cube->img = malloc(sizeof(t_img));

	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	ft_struct_init(argv, cube);
			cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE, "Cube3D");
	cube->img->img = mlx_new_image(cube->mlx_init, cube->MapWidth * SCALE, cube->MapHeight * SCALE);
	cube->img->addr = mlx_get_data_addr(cube->img->img, &cube->img->bpp, &cube->img->size_len, &cube->img->endian);
	ft_print_cube(cube);
	ft_draw(cube);
	ft_free_parsing(cube);
}