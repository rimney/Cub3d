/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 03:00:33 by mrobaii           #+#    #+#             */
/*   Updated: 2023/01/24 00:45:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_img_init(t_img *img)
{
	img->bpp = 0;
	img->endian = 0;
	img->size_len = 0;
	img->addr = NULL;
}

void	init_const_vr(t_cube *cube)
{
	cube->stable->fov = 60 * (M_PI / 180);
	cube->stable->height = cube->MapHeight * SCALE;
	cube->stable->width = cube->MapWidth * SCALE;
	cube->stable->num_of_rays = WINDOW_WIDTH;
}

void	ft_init_player(t_cube *cube)
{
	if (cube->Psp == 'S')
		cube->player->angle = 180 * M_PI / 180;
	else if (cube->Psp == 'N')
		cube->player->angle = 360 * M_PI / 180;
	else if (cube->Psp == 'W')
		cube->player->angle = 270 * M_PI / 180;
	else
		cube->player->angle = 90 * M_PI / 180;
	cube->player->movespeed = 2;
	cube->player->rotationspeed = 1 * (M_PI / 180);
	cube->player->turndirection = 0;
	cube->player->walkdirection = 0;
	cube->P_position_x = cube->P_position_x * SCALE;
	cube->P_position_y = cube->P_position_y * SCALE;
}

void	ft_mlx_init(t_cube *cube)
{
	cube->mlx_init = mlx_init();
	cube->mlx_window = mlx_new_window(cube->mlx_init, WINDOW_WIDTH, \
	WINDOW_HEIGHT, "Cub3D");
}

int	ft_open_file_so(t_cube *cube)
{
	int fd;
	fd = open(cube->SO, O_RDONLY);
	if(fd == -1)
		return (0);
	return (1);	
}

int	ft_open_file_we(t_cube *cube)
{
	int fd;
	fd = open(cube->WE, O_RDONLY);
	if(fd == -1)
		return (0);
	return (1);	
}

int	ft_open_file_no(t_cube *cube)
{
	int fd;
	fd = open(cube->NO, O_RDONLY);
	if(fd == -1)
		return (0);
	return (1);	
}

int	ft_open_file_ea(t_cube *cube)
{
	int fd;
	fd = open(cube->EA, O_RDONLY);
	if(fd == -1)
		return (0);
	return (1);	
}


int	ft_check_file_extensions(t_cube *cube)
{
	if(ft_strcmp(ft_strrchr(cube->SO, '.'), ".xmp") != 0)
		return (0);
	if(ft_strcmp(ft_strrchr(cube->NO, '.'), ".xmp") != 0)
		return (0);
	if(ft_strcmp(ft_strrchr(cube->WE, '.'), ".xmp") != 0)
		return (0);
	if(ft_strcmp(ft_strrchr(cube->EA, '.'), ".xmp") != 0)
		return (0);
	return (1);
}

char	*ft_strdup_texture(char *str)
{
	int i;
	char *ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	while(((size_t)i < ft_strlen(str) - 1) && str[i] != ' ' && str[i] != '\n')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

int	ft_texture_final_check(char *xpm)
{
	char **temp;

	temp = ft_split(xpm, ' ');
	if(ft_count_2d(temp) > 2)
		ft_exit("texture error\n");
	if(temp[0])
	{
		if(ft_strcmp(temp[0], "NO") != 0 || ft_strcmp(temp[0], "SO") != 0 || ft_strcmp(temp[0], "WE") != 0 || ft_strcmp(temp[0], "EA") != 0)
		{
			ft_free_2d(temp);
			ft_exit("texture error\n");
		}
	}
	ft_free_2d(temp);
	return (1);
}

char *ft_get_texture(char *xpm)
{
	char **temp;
	char *t;

	if(!ft_texture_final_check(xpm))
		return (NULL);
	t = xpm;
	temp = ft_split(xpm, ' ');
	if(!temp[1])
		ft_exit("Xpm Error\n");
	xpm = ft_strdup_texture(temp[1]);
	ft_free_2d(temp);
	free(t);
	return (xpm);
}

void	ft_get_textures(t_cube *cube)
{
	cube->NO = ft_get_texture(cube->NO);
	cube->SO = ft_get_texture(cube->SO);
	cube->WE = ft_get_texture(cube->WE);
	cube->EA = ft_get_texture(cube->EA);

	
}


void	ft_textures_init(t_cube *cube)
{
	if(!ft_open_file_so(cube) || !ft_open_file_ea(cube) || !ft_open_file_we(cube) || !ft_open_file_no(cube)) // must protext the .xpm extention
		ft_exit("An Error Has Been Occured While Opening the files");
	if(!ft_check_file_extensions(cube))
		ft_exit("Please check the extensions\n");
	cube->SO_texture = malloc(sizeof(t_img));
	cube->NO_texture = malloc(sizeof(t_img));
	cube->WE_texture = malloc(sizeof(t_img));
	cube->EA_texture = malloc(sizeof(t_img));
	cube->texture = malloc(sizeof(t_img));
	cube->SO_texture->img = mlx_xpm_file_to_image(cube->mlx_init, cube->SO, &cube->SO_texture->width, &cube->SO_texture->height);
	cube->NO_texture->img = mlx_xpm_file_to_image(cube->mlx_init, cube->NO, &cube->NO_texture->width, &cube->NO_texture->height);
	cube->WE_texture->img = mlx_xpm_file_to_image(cube->mlx_init, cube->WE, &cube->WE_texture->width, &cube->WE_texture->height);
	cube->EA_texture->img = mlx_xpm_file_to_image(cube->mlx_init, cube->EA, &cube->EA_texture->width, &cube->EA_texture->height);
	cube->SO_texture->addr = mlx_get_data_addr(cube->SO_texture->img, &cube->SO_texture->bpp, &cube->SO_texture->size_len, &cube->SO_texture->endian);		
	cube->NO_texture->addr = mlx_get_data_addr(cube->NO_texture->img, &cube->NO_texture->bpp, &cube->NO_texture->size_len, &cube->NO_texture->endian);		
	cube->WE_texture->addr = mlx_get_data_addr(cube->WE_texture->img, &cube->WE_texture->bpp, &cube->WE_texture->size_len, &cube->WE_texture->endian);		
	cube->EA_texture->addr = mlx_get_data_addr(cube->EA_texture->img, &cube->EA_texture->bpp, &cube->EA_texture->size_len, &cube->EA_texture->endian);		
	// exit(0);
}
void	ft_struct_init(char **argv, t_cube *cube)
{
	ft_cube_values_init(cube);
	cube->files_f = ft_files_f_init();
	ft_get_xpms(cube, argv);
	ft_get_CF(cube, argv);
	ft_get_map(cube, argv);
	ft_img_init(cube->img);
	ft_init_player(cube);
	init_const_vr(cube);
	// ft_get_textures(cube);
	// exit(0);
	ft_mlx_init(cube);
	ft_textures_init(cube);
}
