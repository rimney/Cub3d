/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 01:30:23 by rimney            #+#    #+#             */
/*   Updated: 2023/01/05 23:18:51 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include "Get_next_line/get_next_line.h"

void	render_background(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (i < cube->MapHeight * SCALE)
	{
		j = 0;
		while(j < cube->MapWidth * SCALE)
		{
			mlx_pixel_put(cube->mlx_init, cube->mlx_window, j, i, 0xFCD088);
			j++;
		}
		i++;
	}
}


void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->size_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int render_block(t_cube *cube, int x, int y, int w, int h, int color)
{
	int i;
	int j;

	i = y;
	if(x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT || y + h >= WINDOW_HEIGHT || w + x >= WINDOW_WIDTH)
		return (0);
	while(i < y + h)
	{
		j = x;
		while (j < w + x)
		{
			my_pixel_put(cube->img, j, i, color);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_render_lines_vertical(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = SCALE;
	while(j < cube->MapWidth * SCALE)
	{
		i = 0;
		while(i < cube->MapHeight * SCALE)
		{
			my_pixel_put(cube->img, j, i, 0xFF0000);
			i++;
		}
		j += SCALE;
	}
}

void	ft_render_lines_horizental(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	j = SCALE;
	while(j < cube->MapHeight * SCALE)
	{
		i = 0;
		while(i < cube->MapWidth * SCALE)
		{
			my_pixel_put(cube->img, i, j, 0xFF0000);
			i++;
		}
		j += SCALE;
	}
}

void	print_map(t_cube *cube)
{
	int i;
	int j;
	
	i = 0;
	while (cube->Map[i])
	{
		j = 0;
		while (cube->Map[i][j])
		{
			printf("[%c]", cube->Map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

}

int	is_a_wall(t_cube *cube, double X, double Y)
{
	int	i;
	int j;
	 // theres another case that i gotta check !!
	i = floor(Y);
	j = floor(X);
	// printf("%d << [i]\n", i);
	// printf("%d << [j]\n", j);
	if(i >= cube->MapHeight || (size_t)j >= ft_strlen(cube->Map[i]))
		return (0);
	// print_map(cube);
	// printf("[%c]\n", cube->Map[i][j]);
	// exit(0);
	if(cube->Map[i][j] && cube->Map[i][j] == '1')
		return (0);
	return (1);
}

void	ft_render_lines(t_cube *cube)
{
	ft_render_lines_vertical(cube);
	ft_render_lines_horizental(cube);
}

int ft_abs(int n) { return ((n > 0) ? n : (n * (-1))); }

void	DDA(t_cube *cube, int x1, int y1, int color)
{
	int dx;
	int dy;
	int steps;
	float Xinc;	
	float Yinc;
	double X;
	double Y;
	int i;

	i = 1;
	dx = x1 - cube->player->x;
	dy = y1 - cube->player->y;
	steps = ft_abs(dx) > ft_abs(dy) ? ft_abs(dx) : ft_abs(dy);
	Xinc = dx / (float)steps;
	Yinc = dy / (float)steps;
	X = cube->player->x;
	Y = cube->player->y;
	while(i <= steps)
	{
		my_pixel_put(cube->img, round(X), round(Y), color);
		i++;
		X += Xinc;
		Y += Yinc; 
	}
}

double	normalize_angle(double angle) // ?????
{
	angle = fmod(angle, (2.0 * PI));
	if(angle < 0)
		angle = (2 * PI) + angle;
	return (angle);
}

double dbp(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_clear_window(t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while(i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH )
		{
			my_pixel_put(cube->img, j, i, 0);
			j++;
		}
		i++;
	}
}

void	cast(t_cube *cube, double rayangle, int index)
{
	double xinterc;
	double yinterc;
	double xstep;
	double ystep;
	double nexthtouchx;
	double nexthtouchy;
	double nextvtouchx;
	double nextvtouchy;
	double wallhitx;
	double wallhity;
	double verwallhitx;
	double verwallhity;
	int	foundhwallhit;

	
	///// H ///////
	foundhwallhit = 0;
	wallhitx = 0;
	wallhity = 0;
	yinterc = floor(cube->player->y / SCALE) * SCALE;
	yinterc += cube->ray[index].isdown ? SCALE : 0;
	xinterc = cube->player->x + (yinterc - cube->player->y) / tan(rayangle);
	ystep = SCALE;
	ystep *= cube->ray[index].isup ? -1 : 1;
	xstep = SCALE / tan(rayangle);
	xstep *= (cube->ray[index].isleft && xstep > 0) ? -1 : 1;
	xstep *= (cube->ray[index].isright && xstep < 0) ? -1 : 1;
	nexthtouchx = xinterc;
	nexthtouchy = yinterc;
	while (nexthtouchx >= 0 && nexthtouchx <= cube->MapWidth * SCALE && nexthtouchy >= 0 && nexthtouchy <= cube->MapHeight * SCALE)
	{
		if(!is_a_wall(cube, nexthtouchx / SCALE, (nexthtouchy - cube->ray[index].isup )/ SCALE))
		{
			foundhwallhit = 1;
			wallhitx = nexthtouchx;
			wallhity = nexthtouchy;
			break;
		}
		else
		{
			nexthtouchx += xstep;
			nexthtouchy += ystep;
		}
	}

	/// V ///////
	int foundvwallhit = 0;
	
	verwallhitx = 0;
	verwallhity = 0;
	xinterc = floor(cube->player->x / SCALE) * SCALE;
	xinterc += cube->ray[index].isright ? SCALE : 0;
	yinterc = cube->player->y + (xinterc - cube->player->x) * tan(rayangle);
	xstep = SCALE;
	xstep *= cube->ray[index].isleft ? -1 : 1;
	ystep = SCALE * tan(rayangle);
	ystep *= (cube->ray[index].isup && ystep > 0) ? -1 : 1;
	ystep *= (cube->ray[index].isdown && ystep < 0) ? -1 : 1;
	nextvtouchx = xinterc;
	nextvtouchy = yinterc;
	
	while (nextvtouchx >= 0 && nextvtouchx <= cube->MapWidth * SCALE && nextvtouchy >= 0 && nextvtouchy <= cube->MapHeight * SCALE)
	{
		if(!is_a_wall(cube, (nextvtouchx - (cube->ray[index].isleft)) / SCALE,  nextvtouchy/ SCALE))
		{
			foundvwallhit = 1;
			verwallhitx = nextvtouchx;
			verwallhity = nextvtouchy;
			break;
		}
		else
		{
			nextvtouchx += xstep;
			nextvtouchy += ystep;
		}
	}

	double horhzd = foundhwallhit ? dbp(cube->player->x, cube->player->y, wallhitx, wallhity) : INT_MAX;
	double verthd = foundvwallhit ? dbp(cube->player->x, cube->player->y, verwallhitx, verwallhity) : INT_MAX;
	cube->ray[index].wallhitx = (horhzd < verthd) ? wallhitx : verwallhitx;
	cube->ray[index].wallhity = (horhzd < verthd) ? wallhity : verwallhity;
	cube->ray[index].distance = horhzd < verthd ? horhzd : verthd;
}

void	ft_cast_rays(t_cube *cube)
{
	// int	columnid;
	double	rayangle;
	int i;

	i = 0;
	// columnid = 0;
	rayangle = cube->player->rotationangle - (cube->ray->fovangle / 2);
	while(i < WINDOW_WIDTH)
	{
		// printf("%f << RAYANGLE B\n", rayangle);
		cube->ray[i].rays = normalize_angle(rayangle);
		cast(cube, cube->ray[i].rays, i);
		//DDA(cube, cube->ray[i].wallhitx, cube->ray[i].wallhity, 0xFF0000);
		// printf("%f << RAYANGLE A\n", rayangle);
		cube->ray[i].isdown = cube->ray[i].rays > 0 && cube->ray[i].rays < PI;
		cube->ray[i].isup = !cube->ray[i].isdown;
		cube->ray[i].isright = cube->ray[i].rays < 0.5 * PI || cube->ray[i].rays > 1.5 * PI;
		cube->ray[i].isleft = !cube->ray[i].isright;
		rayangle += cube->ray[i].fovangle / cube->ray[i].rays_num;
		// printf("%f << rayangle\n", rayangle);
		// printf("%f << fov\n", cube->ray->fovangle);
		// printf("%d << rays num\n", cube->ray->rays_num);
		i++;
		// columnid += 1;
	}
	// exit(0);
	// exit(0);
}

// void	ft_render_rays(t_cube *cube)
// {
// 	int i;
// 	i = 0;

// 	// ft_cast_rays(cube);
// 	while(i < 1)
// 	{
// 		// printf("%f << ray\n", cube->ray->rays[i]);

// 		i++;
// 	}
// 	// exit(0);
// }
void render3D(t_cube *cube)
{
	int i;
	int j;
	double pdistance;
	double dpp;
	double projectionwallheight;
	int wallstripeheight;
	int walltoppixel;
	int wallbottompixel;
	

	i = 0;
	while(i < WINDOW_WIDTH)
	{
		pdistance = cube->ray[i].distance * cos(cube->ray[i].rays - cube->player->rotationangle);
		dpp = (WINDOW_WIDTH / 2) / tan(cube->ray->fovangle / 2);
		projectionwallheight = (SCALE / pdistance) * dpp;
		wallstripeheight = (int)projectionwallheight;
		walltoppixel = (WINDOW_HEIGHT / 2) - (wallstripeheight / 2);
		walltoppixel =  walltoppixel < 0 ? 0 : walltoppixel;
		wallbottompixel = (WINDOW_HEIGHT / 2) + (wallstripeheight / 2);
		wallbottompixel = wallbottompixel > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallbottompixel;
		j = walltoppixel;
		while(j < wallbottompixel)
		{
			my_pixel_put(cube->img, i, j, 0xFFFFFF);
			j++;
		}
		
		i++;
	}
	// exit(0);
}


void	ft_render_player(t_cube *cube)
{
	double player_X;
	double player_Y;
	double movestep;
	// player_X = 
	movestep = cube->player->walkdirection * cube->player->movespeed;
	
	cube->player->rotationangle += (cube->player->turndirection * cube->player->rotationspeed);
	player_X = cube->player->x + cos(cube->player->rotationangle) * movestep;
	player_Y = cube->player->y + sin(cube->player->rotationangle) * movestep;
	// printf("%f << X\n", player_X / SCALE);
	// printf("%f << Y\n", player_Y / SCALE);
	// printf("[[%c]]]\n", cube->Map[(int)(player_Y / SCALE)][(int)(player_X / SCALE)]);
	if(is_a_wall(cube, player_X / SCALE, player_Y / SCALE))
	{
		cube->player->x = player_X;
		cube->player->y = player_Y;
	}
	// cube->player->y += sin(cube->player->rotationangle) * movestep;
	//DDA(cube, cube->player->x + cos(cube->player->rotationangle) * SCALE, cube->player->y + sin(cube->player->rotationangle)  * SCALE, 0xFF0000);
	//render_block(cube, cube->player->x, cube->player->y, SCALE / 10, SCALE / 10 , 0xFF0000);
	ft_clear_window(cube);
	ft_cast_rays(cube);
	render3D(cube);
	//ft_render_rays(cube);
}



int	key_press(int key, t_cube *cube)
{
	if(key == UP_KEY || key == W_KEY)
		cube->player->walkdirection = 1;
	else if (key == DOWN_KEY || key == S_KEY)
		cube->player->walkdirection = -1;
	else if (key == RIGHT_KEY)
		cube->player->turndirection = 1;
	else if (key == LEFT_KEY)
		cube->player->turndirection = -1;
	return (0);
}

int	key_release(int key, t_cube *cube)
{
	if(key == UP_KEY || key == W_KEY)
		cube->player->walkdirection = 0;
	else if (key == DOWN_KEY || key == S_KEY)
		cube->player->walkdirection = 0;
	else if (key == RIGHT_KEY)
		cube->player->turndirection = 0;
	else if (key == LEFT_KEY)
		cube->player->turndirection = 0;
	return (0);
}


int	render(t_cube *cube)
{
	int i;
	int j;
	int ii;
	int jj;

	i = 0;
	j = 0;
	ii = 0;
	jj = 0;
	if(cube->render)
		mlx_clear_window(cube->mlx_init, cube->mlx_window);
	while(i < cube->MapHeight)
	{
		j = 0;
		while((size_t)j < ft_strlen(cube->Map[i]))
		{
			// if(cube->Map[i][j] == '1')
			// 	render_block(cube, j * SCALE, i * SCALE, SCALE, SCALE, 0xFFFFFF);
			// if(cube->Map[i][j] == '0')
			// 	render_block(cube, j * SCALE, i * SCALE, SCALE, SCALE, 0x0000FF);
			// if(is_a_direction(cube->Map[i][j]))
			// 	render_block(cube, j * SCALE, i * SCALE, SCALE, SCALE, 0x0000FF);
			 j++;
		}
		i++;
	}
	//ft_render_lines(cube);
	ft_render_player(cube);
	 mlx_put_image_to_window(cube->mlx_init, cube->mlx_window, cube->img->img ,0, 0);
	cube->render = 1;
	return (0);
}

void	ft_ray_init(t_cube *cube, t_ray *ray)
{
	int i;

	i = 0;
	ray = ft_calloc(WINDOW_WIDTH, sizeof(t_ray));
	while(i < WINDOW_WIDTH)
	{
		ray[i].fovangle = 60 * (PI / 180);
		ray[i].wall_strip_width = 1;
		ray[i].rays_num = WINDOW_WIDTH;
		ray[i].rays = 0;
		ray[i].wallhitx = 0;
		ray[i].wallhity = 0;
		ray[i].distance = 0;
		ray[i].isup = 0;
		ray[i].isdown = 0;
		i++;
	}
	cube->ray = ray;
}

void	ft_create_window(t_cube *cube, t_img *img)
{
	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, WINDOW_WIDTH, WINDOW_HEIGHT, "cube");
	img->img = mlx_new_image(cube->mlx_init, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->addr = mlx_get_data_addr(cube->img->img, &img->bpp, &img->size_len, &img->endian);
	// ft_render_player(cube);
	cube->img = img;
	mlx_hook(cube->mlx_window, 2, 0, key_press, cube);
	mlx_hook(cube->mlx_window, 3, 0, key_release, cube);
	mlx_loop_hook(cube->mlx_init, render, cube);
	mlx_loop(cube->mlx_init);
}

void	ft_init_player(t_cube *cube, t_player *player)
{
	player->x = cube->P_position_x * SCALE;
	player->y = cube->P_posotion_y * SCALE;
	player->radius = 3;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotationangle = M_PI_2;
	player->movespeed = 2.0;
	player->rotationspeed = 3 * (M_PI / 180);
	cube->player = player;
}

void	ft_img_init(t_img *img)
{
	img->bpp = 0;
	img->endian = 0;
	img->size_len = 0;
	img->addr = NULL;
}



t_cube	*ft_struct_init(char **argv, t_img *img, t_player *player, t_ray *ray)
{
	t_cube *cube;
	cube = malloc(sizeof(t_cube));
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	ft_init_player(cube, player);
	ft_ray_init(cube, ray);
	ft_img_init(img);
	cube->img = img;
	ft_create_window(cube, img);

	return (cube);
}

int main(int argc, char **argv)
{
    t_cube		*cube;
	t_img		img;
	t_player	player;
	t_ray		ray;
	if(argc !=  2)
	{
		printf("Check the args !\n");
		exit(0);
	}
	cube = ft_struct_init(argv, &img, &player, &ray);
	ft_print_cube(cube);
	ft_free_parsing(cube);
    // system("leaks Cub3d");
}