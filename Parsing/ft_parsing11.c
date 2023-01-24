/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 03:30:34 by rimney            #+#    #+#             */
/*   Updated: 2023/01/24 18:06:17 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_allocate_textures(t_cube *cube)
{
	cube->so_texture = malloc(sizeof(t_img));
	cube->no_texture = malloc(sizeof(t_img));
	cube->we_texture = malloc(sizeof(t_img));
	cube->ea_texture = malloc(sizeof(t_img));
	cube->texture = malloc(sizeof(t_img));
}

void	ft_assign_data(t_cube *cube)
{
	cube->so_texture->img
		= mlx_xpm_file_to_image(cube->mlx_init,
			cube->so, &cube->so_texture->width,
			&cube->so_texture->height);
	cube->no_texture->img
		= mlx_xpm_file_to_image(cube->mlx_init,
			cube->no, &cube->no_texture->width,
			&cube->no_texture->height);
	cube->we_texture->img
		= mlx_xpm_file_to_image(cube->mlx_init,
			cube->we, &cube->we_texture->width, &cube->we_texture->height);
	cube->ea_texture->img
		= mlx_xpm_file_to_image(cube->mlx_init,
			cube->ea, &cube->ea_texture->width, &cube->ea_texture->height);
}

int	ft_check_addr(t_cube *cube)
{
	if (!cube->so_texture->img)
		return (0);
	else if (!cube->no_texture->img)
		return (0);
	else if (!cube->we_texture->img)
		return (0);
	else if (!cube->ea_texture->img)
		return (0);
	return (1);
}

void	ft_assign_addr(t_cube *cube)
{
	if (!ft_check_addr(cube))
		ft_exit("Xpm Error");
	cube->so_texture->addr
		= mlx_get_data_addr(cube->so_texture->img,
			&cube->so_texture->bpp, &cube->so_texture->size_len,
			&cube->so_texture->endian);
	cube->no_texture->addr
		= mlx_get_data_addr(cube->no_texture->img,
			&cube->no_texture->bpp,
			&cube->no_texture->size_len,
			&cube->no_texture->endian);		
	cube->we_texture->addr
		= mlx_get_data_addr(cube->we_texture->img,
			&cube->we_texture->bpp, &cube->we_texture->size_len,
			&cube->we_texture->endian);		
	cube->ea_texture->addr
		= mlx_get_data_addr(cube->ea_texture->img,
			&cube->ea_texture->bpp,
			&cube->ea_texture->size_len,
			&cube->ea_texture->endian);
}

void	ft_textures_init(t_cube *cube)
{
	if (!ft_open_file_so(cube) || !ft_open_file_ea(cube)
		|| !ft_open_file_we(cube)
		|| !ft_open_file_no(cube))
		ft_exit("An Error Has Been Occured While Opening the files");
	if (!ft_check_file_extensions(cube))
		ft_exit("Please check the extensions\n");
	ft_allocate_textures(cube);
	ft_assign_data(cube);
	ft_assign_addr(cube);
}
